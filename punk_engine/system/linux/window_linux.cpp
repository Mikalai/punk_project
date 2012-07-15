#ifdef __linux__

#include <stdio.h>
#include "window_linux.h"
#include "../../ogldriver/extensions.h"
#include <X11/keysym.h>
#include <GL/glx.h>
#include "../event_manager.h"
#include "../error.h"

namespace System
{
    Display* Window::GetDisplay()
    {
        return display;
    }

    ::Window Window::GetWindow()
    {
        return window;
    }

    __GLXcontextRec* Window::GetOpenGLContext()
    {
        return ctx;
    }

    Colormap* Window::GetColorMap()
    {
        return &colorMap;
    }

    Window::Window()
    {
        display = XOpenDisplay(NULL);
        if (display == NULL)
            throw SystemError("XWindow: can't open display");

        static int visual_attribs[] =
        {
            GLX_X_RENDERABLE,       true,
            GLX_DRAWABLE_TYPE,      GLX_WINDOW_BIT,
            GLX_RENDER_TYPE,        GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE,      GLX_TRUE_COLOR,
            GLX_RED_SIZE,           8,
            GLX_GREEN_SIZE,         8,
            GLX_BLUE_SIZE,          8,
            GLX_ALPHA_SIZE,         8,
            GLX_DEPTH_SIZE,         24,
            GLX_STENCIL_SIZE,       8,
            GLX_DOUBLEBUFFER,       true,
            None
        };

        int glx_major, glx_minor;

        if (!glXQueryVersion(display, &glx_minor, &glx_major) ||
            (( glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
        {
            printf("GLX VERSION: %d.%d\n", glx_major, glx_minor);
            throw SystemError("Bad glx version");
        }

        int fbcount;
        GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display),
                                             visual_attribs, &fbcount);

        if (!fbc)
        {
            printf("failed to retrieve framebuffer config\n");
            throw SystemError("unable to create framebuffer");
        }

        printf("found %d matching framebuffers", fbcount);

        // Pick the FB config/visual with the most samples per pixel
        printf( "Getting XVisualInfos\n" );
        int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

        for (int i = 0; i < fbcount; i++ )
        {
            XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i] );
            if ( vi )
            {
                int samp_buf, samples;
                glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
                glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

                printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
                        " SAMPLES = %d\n",
                        i, vi -> visualid, samp_buf, samples );

                if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
                    best_fbc = i, best_num_samp = samples;
                if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                    worst_fbc = i, worst_num_samp = samples;
            }
            XFree( vi );
        }

        GLXFBConfig bestFbc = fbc[ best_fbc ];

        // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
        XFree( fbc );

        // Get a visual
        XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc );
        printf( "Chosen visual ID = 0x%x\n", vi->visualid );

        printf( "Creating colormap\n" );
        XSetWindowAttributes swa;
        swa.colormap = colorMap = XCreateColormap( display,
                                                   RootWindow( display, vi->screen ),
                                                   vi->visual, AllocNone );
        swa.background_pixmap = None ;
        swa.border_pixel      = 0;
        swa.event_mask        = KeyPressMask | PointerMotionMask | StructureNotifyMask
                                | ButtonPressMask;

        printf( "Creating window\n" );
        window = XCreateWindow( display,
                                RootWindow( display, vi->screen ),
                                0, 0, 800, 600, 0, vi->depth, InputOutput,
                                vi->visual,
                                CWBorderPixel|CWColormap|CWEventMask, &swa );
        if ( !window )
        {
            printf( "Failed to create window.\n" );
            throw SystemError("Can't create XWindow");
        }

        // Done with the visual info data
        XFree( vi );

        XStoreName( display, window, "GL 2.0 Window" );

        printf( "Mapping window\n" );
        XMapWindow(display, window);
        printf( "Ok...\n");
        // Get the default screen's GLX extension list
        const char *glxExts = glXQueryExtensionsString( display,
                                                        DefaultScreen( display ) );

        printf("Extesion string is %s\n", glxExts);
        // NOTE: It is not necessary to create or make current to a context before
        // calling glXGetProcAddressARB
        printf("glXGetProcAddressARB %p\n", glXGetProcAddressARB);
        printf("glXGetProcAddress %p\n", glXGetProcAddress);
        glXCreateContextAttribsARB = 0;
        printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);
        glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

        printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);

        // Check for the GLX_ARB_create_context extension string and the function.
        // If either is not present, use GLX 1.3 context creation method.
        if ( !Extensions::IsSupported("GLX_ARB_create_context" ) ||
             !glXCreateContextAttribsARB )
        {
            printf( "glXCreateContextAttribsARB() not found"
                    " ... using old-style GLX context\n" );
            printf("glXCreateNewContext address is %p\n", glXCreateContext);
            ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
        }

        // If it does, try to get a GL 3.0 context!
        else
        {
            int context_attribs[] =
            {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
                GLX_CONTEXT_MINOR_VERSION_ARB, 1,
                //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                None
            };

            printf( "Creating context\n" );
            ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
                                              True, context_attribs );

            // Sync to ensure any errors generated are processed.
            XSync( display, False );
            if ( ctx )
                printf( "Created GL 2.1 context\n" );
            else
            {
                // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
                // When a context version below 3.0 is requested, implementations will
                // return the newest context version compatible with OpenGL versions less
                // than version 3.0.
                // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
                context_attribs[1] = 1;
                // GLX_CONTEXT_MINOR_VERSION_ARB = 0
                context_attribs[3] = 0;

                printf( "Failed to create GL 3.0 context"
                        " ... using old-style GLX context\n" );
                ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
                                                  True, context_attribs );
            }
        }

        // Sync to ensure any errors generated are processed.
        XSync( display, False );

        if (!ctx )
        {
            printf( "Failed to create an OpenGL context\n" );
            throw SystemError("Can't create glx context");
        }

        // Verifying that context is a direct context
        if ( ! glXIsDirect ( display, ctx ) )
        {
            printf( "Indirect GLX rendering context obtained\n" );
        }
        else
        {
            printf( "Direct GLX rendering context obtained\n" );
        }

        printf( "Making context current\n" );
        glXMakeCurrent( display, window, ctx );

        printf( "Window created \n");
    }

    int Window::Loop()
    {
        XEvent event;
        while (1)
        {
            do
            {
                //XNextEvent(display, &event);
                if (!XCheckWindowEvent(display, window, -1l, &event))
                    break;

                switch (event.type)
                {
                case KeyPress:
                case KeyRelease:
                    {
                        bool press = event.type == KeyPress;                        
                        int charKey = 0;
                        int key = 0;
                        KeySym     keysym;
                        XKeyEvent *kevent;
                        char       buffer[1];
                        /* It is necessary to convert the keycode to a
                     * keysym before checking if it is an escape */
                        kevent = (XKeyEvent *) &event;                        
                        if (XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) == 1)
                        {
                            switch(keysym)
                            {                           
                            case XK_Alt_L:
                                buttons[key = PUNK_KEY_LEFT_ALT] = press;
                                break;
                            case XK_Alt_R:
                                buttons[key = PUNK_KEY_RIGHT_ALT] = press;
                                break;
                            case XK_Tab:
                                buttons[key = PUNK_KEY_TAB] = press;
                                break;
                            case XK_Caps_Lock:
                                buttons[key = PUNK_KEY_CAPSLOCK] = press;
                                break;
                            case XK_Page_Up:
                                buttons[key = PUNK_KEY_PAGE_UP] = press;
                                break;
                            case XK_Page_Down:
                                buttons[key = PUNK_KEY_PAGE_DOWN] = press;
                                break;
                            case XK_Return:
                                buttons[key = PUNK_KEY_ENTER] = press;
                                break;
                            case XK_Escape:
                                buttons[key = PUNK_KEY_ESCAPE] = press;
                                break;
                            case XK_space:
                                charKey = ' ';
                                buttons[key = PUNK_KEY_SPACE] = press;
                                break;
                            case XK_End:
                                buttons[key = PUNK_KEY_END] = press;
                                break;
                            case XK_Home:
                                buttons[key = PUNK_KEY_HOME] = press;
                                break;
                            case XK_Left:
                                buttons[key = PUNK_KEY_LEFT] = press;
                                break;
                            case XK_Up:
                                buttons[key = PUNK_KEY_UP                 ]= press;
                                break;
                            case XK_Right:
                                buttons[key = PUNK_KEY_RIGHT              ] = press;
                                break;
                            case XK_Down:
                                buttons[key = PUNK_KEY_DOWN               ] = press;
                                break;
                            case XK_Insert:
                                buttons[key = PUNK_KEY_INSERT             ] = press;
                                break;
                            case XK_Delete:
                                buttons[key = PUNK_KEY_DELETE             ] = press;
                                break;
                            case XK_0:
                                charKey = '0';
                                buttons[key = PUNK_KEY_0               ] = press;
                                break;
                            case XK_1:
                                charKey = '1';
                                buttons[key = PUNK_KEY_1               ] = press;
                                break;
                            case XK_2:
                                charKey = '2';
                                buttons[key = PUNK_KEY_2               ] = press;
                                break;
                            case XK_3:
                                charKey = '3';
                                buttons[key = PUNK_KEY_3               ] = press;
                                break;
                            case XK_4:
                                charKey = '4';
                                buttons[key = PUNK_KEY_4               ] = press;
                                break;
                            case XK_5:
                                charKey = '5';
                                buttons[key = PUNK_KEY_5               ] = press;
                                break;
                            case XK_6:
                                charKey = '6';
                                buttons[key = PUNK_KEY_6               ] = press;
                                break;
                            case XK_7:
                                charKey = '7';
                                buttons[key = PUNK_KEY_7               ] = press;
                                break;
                            case XK_8:
                                charKey = '8';
                                buttons[key = PUNK_KEY_8               ] = press;
                                break;
                            case XK_9:
                                charKey = '9';
                                buttons[key = PUNK_KEY_9               ] = press;
                                break;
                            case XK_A:
                                charKey = 'A';
                                buttons[key = PUNK_KEY_A               ] = press;
                                break;
                            case XK_a:
                                charKey = 'a';
                                buttons[key = PUNK_KEY_A               ] = press;
                                break;
                            case XK_B:
                                charKey = 'B';
                                buttons[key = PUNK_KEY_B               ] = press;
                                break;
                            case XK_b:
                                charKey = 'b';
                                buttons[key = PUNK_KEY_B               ] = press;
                                break;
                            case XK_C:
                                charKey = 'C';
                                buttons[key = PUNK_KEY_C               ] = press;
                                break;
                            case XK_c:
                                charKey = 'c';
                                buttons[key = PUNK_KEY_C               ] = press;
                                break;
                            case XK_D:
                                charKey = 'D';
                                buttons[key = PUNK_KEY_D               ] = press;
                                break;
                            case XK_d:
                                charKey = 'd';
                                buttons[key = PUNK_KEY_D               ] = press;
                                break;
                            case XK_E:
                                charKey = 'E';
                                buttons[key = PUNK_KEY_E               ] = press;
                                break;
                            case XK_e:
                                charKey = 'e';
                                buttons[key = PUNK_KEY_E               ] = press;
                                break;
                            case XK_F:
                                charKey = 'F';
                                buttons[key = PUNK_KEY_F               ] = press;
                                break;
                            case XK_f:
                                charKey = 'f';
                                buttons[key = PUNK_KEY_F               ] = press;
                                break;
                            case XK_G:
                                charKey = 'G';
                                buttons[key = PUNK_KEY_G               ] = press;
                                break;
                            case XK_g:
                                charKey = 'g';
                                buttons[key = PUNK_KEY_G               ] = press;
                                break;
                            case XK_H:
                                charKey = 'H';
                                buttons[key = PUNK_KEY_H               ] = press;
                                break;
                            case XK_h:
                                charKey = 'h';
                                buttons[key = PUNK_KEY_H               ] = press;
                                break;
                            case XK_I:
                                charKey = 'I';
                                buttons[key = PUNK_KEY_I               ] = press;
                                break;
                            case XK_i:
                                charKey = 'i';
                                buttons[key = PUNK_KEY_I               ] = press;
                                break;
                            case XK_J:
                                charKey = 'J';
                                buttons[key = PUNK_KEY_J               ] = press;
                                break;
                            case XK_j:
                                charKey = 'j';
                                buttons[key = PUNK_KEY_J               ] = press;
                                break;
                            case XK_K:
                                charKey = 'K';
                                buttons[key = PUNK_KEY_K               ] = press;
                                break;
                            case XK_k:
                                charKey = 'k';
                                buttons[key = PUNK_KEY_K               ] = press;
                                break;
                            case XK_L:
                                charKey = 'L';
                                buttons[key = PUNK_KEY_L               ] = press;
                                break;
                            case XK_l:
                                charKey = 'l';
                                buttons[key = PUNK_KEY_L               ] = press;
                                break;
                            case XK_M:
                                charKey = 'M';
                                buttons[key = PUNK_KEY_M               ] = press;
                                break;
                            case XK_m:
                                charKey = 'm';
                                buttons[key = PUNK_KEY_M               ] = press;
                                break;
                            case XK_N:
                                charKey = 'N';
                                buttons[key = PUNK_KEY_N               ] = press;
                                break;
                            case XK_n:
                                charKey = 'n';
                                buttons[key = PUNK_KEY_N               ] = press;
                                break;
                            case XK_O:
                                charKey = 'O';
                                buttons[key = PUNK_KEY_O               ] = press;
                                break;
                            case XK_o:
                                charKey = 'o';
                                buttons[key = PUNK_KEY_O               ] = press;
                                break;
                            case XK_P:
                                charKey = 'P';
                                buttons[key = PUNK_KEY_P               ] = press;
                                break;
                            case XK_p:
                                charKey = 'p';
                                buttons[key = PUNK_KEY_P               ] = press;
                                break;
                            case XK_Q:
                                charKey = 'Q';
                                buttons[key = PUNK_KEY_Q               ] = press;
                                break;
                            case XK_q:
                                charKey = 'q';
                                buttons[key = PUNK_KEY_Q               ] = press;
                                break;
                            case XK_R:
                                charKey = 'R';
                                buttons[key = PUNK_KEY_R               ] = press;
                                break;
                            case XK_r:
                                charKey = 'r';
                                buttons[key = PUNK_KEY_R               ] = press;
                                break;
                            case XK_S:
                                charKey = 'S';
                                buttons[key = PUNK_KEY_S               ] = press;
                                break;
                            case XK_s:
                                charKey = 's';
                                buttons[key = PUNK_KEY_S               ] = press;
                                break;
                            case XK_T:
                                charKey = 'T';
                                buttons[key = PUNK_KEY_T               ] = press;
                                break;
                            case XK_t:
                                charKey = 't';
                                buttons[key = PUNK_KEY_T               ] = press;
                                break;
                            case XK_U:
                                charKey = 'U';
                                buttons[key = PUNK_KEY_U               ] = press;
                                break;
                            case XK_u:
                                charKey = 'u';
                                buttons[key = PUNK_KEY_U               ] = press;
                                break;
                            case XK_V:
                                charKey = 'V';
                                buttons[key = PUNK_KEY_V               ] = press;
                                break;
                            case XK_v:
                                charKey = 'v';
                                buttons[key = PUNK_KEY_V               ] = press;
                                break;
                            case XK_W:
                                charKey = 'W';
                                buttons[key = PUNK_KEY_W               ] = press;
                                break;
                            case XK_w:
                                charKey = 'w';
                                buttons[key = PUNK_KEY_W               ] = press;
                                break;
                            case XK_X:
                                charKey = 'X';
                                buttons[key = PUNK_KEY_X               ] = press;
                                break;
                            case XK_x:
                                charKey = 'x';
                                buttons[key = PUNK_KEY_X               ] = press;
                                break;
                            case XK_Y:
                                charKey = 'Y';
                                buttons[key = PUNK_KEY_Y               ] = press;
                                break;
                            case XK_y:
                                charKey = 'y';
                                buttons[key = PUNK_KEY_Y               ] = press;
                                break;
                            case XK_Z:
                                charKey = 'Z';
                                buttons[key = PUNK_KEY_Z               ] = press;
                                break;
                            case XK_z:
                                charKey = 'z';
                                buttons[key = PUNK_KEY_Z               ] = press;
                                break;
                            case XK_KP_0:
                                buttons[key = PUNK_KEY_NUM0               ] = press;
                                break;
                            case XK_KP_1:
                                buttons[key = PUNK_KEY_NUM1               ] = press;
                                break;
                            case XK_KP_2:
                                buttons[key = PUNK_KEY_NUM2               ] = press;
                                break;
                            case XK_KP_3:
                                buttons[key = PUNK_KEY_NUM3               ] = press;
                                break;
                            case XK_KP_4:
                                buttons[key = PUNK_KEY_NUM4               ] = press;
                                break;
                            case XK_KP_5:
                                buttons[key = PUNK_KEY_NUM5               ] = press;
                                break;
                            case XK_KP_6:
                                buttons[key = PUNK_KEY_NUM6               ] = press;
                                break;
                            case XK_KP_7:
                                buttons[key = PUNK_KEY_NUM7               ] = press;
                                break;
                            case XK_KP_8:
                                buttons[key = PUNK_KEY_NUM8               ] = press;
                                break;
                            case XK_KP_9:
                                buttons[key = PUNK_KEY_NUM9               ] = press;
                                break;
                            case XK_F1:
                                buttons[key = PUNK_KEY_F1               ] = press;
                                break;
                            case XK_F2:
                                buttons[key = PUNK_KEY_F2               ] = press;
                                break;
                            case XK_F3:
                                buttons[key = PUNK_KEY_F3               ] = press;
                                break;
                            case XK_F4:
                                buttons[key = PUNK_KEY_F4               ] = press;
                                break;
                            case XK_F5:
                                buttons[key = PUNK_KEY_F5               ] = press;
                                break;
                            case XK_F6:
                                buttons[key = PUNK_KEY_F6               ] = press;
                                break;
                            case XK_F7:
                                buttons[key = PUNK_KEY_F7               ] = press;
                                break;
                            case XK_F8:
                                buttons[key = PUNK_KEY_F8               ] = press;
                                break;
                            case XK_F9:
                                buttons[key = PUNK_KEY_F9               ] = press;
                                break;
                            case XK_F10:
                                buttons[key = PUNK_KEY_F10               ] = press;
                                break;
                            case XK_F11:
                                buttons[key = PUNK_KEY_F11               ] = press;
                                break;
                            case XK_F12:
                                buttons[key = PUNK_KEY_F12               ] = press;
                                break;
                            case XK_Shift_L:
                                buttons[key = PUNK_KEY_LEFT_SHIFT               ] = press;
                                break;
                            case XK_Shift_R:
                                buttons[key = PUNK_KEY_RIGHT_SHIFT               ] = press;
                                break;
                            case XK_Control_L:
                                buttons[key = PUNK_KEY_LEFT_CONTROL               ] = press;
                                break;
                            case XK_Control_R:
                                buttons[key = PUNK_KEY_RIGHT_CONTROL               ] = press;
                                break;
                            }

                            if (press)
                            {
                                KeyDownEvent* e = KeyDownEvent::Raise();
                                e->x = kevent->x;
                                e->y = kevent->y;
                                e->key = key;
                                EventManager::Instance()->FixEvent(e);
                            }
                            else
                            {
                                KeyUpEvent* e = KeyUpEvent::Raise();
                                e->x = kevent->x;
                                e->y = kevent->y;
                                e->key = key;
                                EventManager::Instance()->FixEvent(e);
                            }

                            if (charKey != 0 && press)
                            {
                                KeyCharEvent* e = KeyCharEvent::Raise();
                                e->x = kevent->x;
                                e->y = kevent->y;
                                e->key = key;
                                EventManager::Instance()->FixEvent(e);
                            }
                        }
                        break;
                    }
                case MotionNotify:
                    {
                        MouseMoveEvent* e = MouseMoveEvent::Raise();
                        e->x = event.xmotion.x;
                        e->y = event.xmotion.y;
                        /*event->controlKey = (bool)(wParam & MK_CONTROL);
                    event->leftButton = (bool)(wParam & MK_LBUTTON);
                    event->middleButton = (bool)(wParam & MK_MBUTTON);
                    event->rightButton = (bool)(wParam & MK_RBUTTON);
                    event->shiftButton = (bool)(wParam & MK_SHIFT);
                    event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
                    event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
                        EventManager::Instance()->FixEvent(e);
                        break;
                    }
                case ButtonPress:
                case ButtonRelease:
                    {
                        bool press = event.type == ButtonPress;
                        int k = 10;
                        switch (event.xbutton.button)
                        {
                        case 1:         //LEFT
                            {
                                if (press)
                                {

                                }
                            }
                            break;
                        case 2:         //Middle
                            break;
                        case 3:         //Right
                            break;
                        case 4:         //Whell +
                            {
                                MouseWheelEvent* e = MouseWheelEvent::Raise();
                                e->x = event.xbutton.x;
                                e->y = event.xbutton.y;                                
                                e->delta = 1;
                                /*event->controlKey = (bool)(wParam & MK_CONTROL);
                                event->leftButton = (bool)(wParam & MK_LBUTTON);
                                event->middleButton = (bool)(wParam & MK_MBUTTON);
                                event->rightButton = (bool)(wParam & MK_RBUTTON);
                                event->shiftButton = (bool)(wParam & MK_SHIFT);
                                event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
                                event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
                                EventManager::Instance()->FixEvent(e);
                            }
                            break;
                        case 5:         //wheel -
                            {

                                MouseWheelEvent* e = MouseWheelEvent::Raise();
                                e->x = event.xbutton.x;
                                e->y = event.xbutton.y;
                                e->delta = -1;
                                /*event->controlKey = (bool)(wParam & MK_CONTROL);
                            event->leftButton = (bool)(wParam & MK_LBUTTON);
                            event->middleButton = (bool)(wParam & MK_MBUTTON);
                            event->rightButton = (bool)(wParam & MK_RBUTTON);
                            event->shiftButton = (bool)(wParam & MK_SHIFT);
                            event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
                            event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
                                EventManager::Instance()->FixEvent(e);
                                break;
                            }
                        }                        
                    }
                }
            }
            while (XPending(display)); /* loop to compress events */

            EventManager::Instance()->FixEvent(IdleEvent::Raise());
            EventManager::Instance()->Process();

        }
    }

    void Window::SubscribeHandler(unsigned message, Handler handler)
    {
        m_handlers.insert(std::make_pair(message, handler));
    }

    void Window::UnsubscribeHandler(unsigned message, Handler handler)
    {
        std::multimap<unsigned, Handler>::iterator lb = m_handlers.lower_bound(message);
        std::multimap<unsigned, Handler>::iterator ub = m_handlers.upper_bound(message);
        std::multimap<unsigned, Handler>::iterator at = m_handlers.end();
        for (std::multimap<unsigned, Handler>::iterator i = lb; i != ub; i++)
        {
            if ((*i).second == handler)
            {
                at = i;
                break;
            }
        }
        if (at != m_handlers.end())
        {
            m_handlers.erase(at);
        }
        else
            throw SystemError("Handler was not subscribed");
    }

    Window::~Window()
    {
        glXMakeCurrent( display, 0, 0 );
        glXDestroyContext( display, ctx );
        XDestroyWindow( display, window );
        XFreeColormap( display, colorMap );
        XCloseDisplay( display );
    }

}

#endif  // __linux__
