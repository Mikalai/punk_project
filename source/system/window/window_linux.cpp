#ifdef __gnu_linux__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/keysym.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPbuffer;
typedef XID GLXPixmap;
typedef XID GLXWindow;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXDrawable;
typedef XID GLXContextID;

#include <stdio.h>
#include <algorithm>

#include "../../math/helper.h"
#include "window.h"
#include "../errors/module.h"
#include "../event_manager.h"
#include "../logger.h"
#include "../input/module.h"
#include "../timer.h"
#include "../concurrency/module.h"

namespace System
{
    struct Window::Impl
    {        
        ::Window m_window;
        // Screen* m_screen;
        Colormap m_color_map;
        WindowAdapter* m_adapter;
        bool m_exit_main_loop;
        XSetWindowAttributes m_swa;
        Atom wmDeleteWindow;

        Impl(WindowAdapter* adapter, const WindowDesc& desc);
        ~Impl();
        int GetDesktopWidth() const;
        int GetDesktopHeight() const;
        int GetDesktopBitsPerPixel() const;
        int GetDesktopRefreshRate() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        void ShowCursor(bool value);
        void SetSize(int width, int height);
        void SetPosition(int x, int y);
        int Loop();
        void BreakMainLoop();
        bool IsClosed();
        void SetTitle(const string& text);
        const string GetTitle() const;
        void Quite();
        void DrawPixel(int x, int y);
        void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        void DrawLine(int x1, int y1, int x2, int y2);
        int DecodeKey(KeySym keysym, int& charKey, bool press);
        void OnKeyPressRelease(XKeyEvent *event);
        void OnMousePressRelease(XEvent *event);

        void MouseMoveProc(Event* e);
        void MouseWheelProc(Event* e);
        void KeyDownProc(Event* e);
        void KeyUpProc(Event* e);
        void KeyCharProc(Event* e);
        void MouseLeftButtonDownProc(Event* e);
        void MouseLeftButtonUpProc(Event* e);
        void MouseRightButtonDownProc(Event* e);
        void MouseRightButtonUpProc(Event* e);
        void MouseMiddleButtonDownProc(Event* e);
        void MouseMiddleButtonUpProc(Event* e);
        void WindowResizeProc(Event* e);
        void MouseEnterProc(Event* e);
        void MouseLeaveProc(Event* e);
        void SetFocusedProc(Event* e);
        void SetUnfocusedProc(Event* e);
        void KeyWcharProc(Event* e);
        void MouseHooverProc(Event* e);
        void IdleEventProc(Event* e);
        void WindowCloseProc();

        int x_prev;
        int y_prev;
        int x;
        int y;
        bool m_left_button;
        bool m_right_button;
        bool m_middle_button;

        Display* m_display;
    };

    Window::Impl::Impl(WindowAdapter* adapter, const WindowDesc& desc)
    {
        x_prev = 0;
        y_prev = 0;
        y = 0;
        m_left_button = false;
        m_right_button = false;
        m_middle_button = false;
        m_exit_main_loop = false;
        m_adapter = adapter;
        m_display = XOpenDisplay(NULL);
        //m_screen = XDefaultScreenOfDisplay(m_display);
        if (m_display == NULL) {
            fprintf(stderr, "Cannot open display\n");
            exit(1);
        }

        int screen = DefaultScreen(m_display);
        memset(&m_swa, 0, sizeof(m_swa));
        m_swa.border_pixel      = WhitePixel(m_display,screen);
        m_swa.background_pixel = BlackPixel(m_display, screen);

        //        m_swa.colormap = XCreateColormap(m_display,
        //                                       RootWindow( m_display, m_screen),
        //                                       XDefaultVisual(m_display, m_screen), AllocNone);
        //        swa.event_mask        = KeyPressMask
        //                                | ExposureMask
        //                                | ButtonPressMask
        //                                | StructureNotifyMask;



        printf("Creating window\n");
        m_window = XCreateWindow(m_display, DefaultRootWindow(m_display),
                                 desc.m_x, desc.m_y, desc.m_width, desc.m_height,
                                 0, DefaultDepth(m_display, screen), CopyFromParent, CopyFromParent, CWBackPixel|CWBorderPixel/*|CWColormap/*|CWEventMask*/, &m_swa);

        XStoreName(m_display, m_window, "PunkEngine");
        XSetIconName(m_display, m_window, "PunkEngine");
        XSetCommand(m_display, m_window, 0, 0);
        XFlush(m_display);


        //        unsigned long white = WhitePixel(m_display,screen);
        //        unsigned long black = BlackPixel(m_display,screen);


        //        m_window = XCreateSimpleWindow(m_display,
        //                                     DefaultRootWindow(m_display),
        //                                     50, 50,   // origin
        //                                     200, 200, // size
        //                                     0, black, // border
        //                                     white );  // backgd

        //        XSetStandardProperties(m_display, m_window, "PunkEngine", "Icon", None, 0, 0, 0);
        XMapWindow(m_display, m_window);
        int eventMask = ButtonPressMask|ButtonReleaseMask|KeyPressMask|ExposureMask|StructureNotifyMask;
        XSelectInput(m_display, m_window, eventMask); // override prev

        wmDeleteWindow = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &wmDeleteWindow, 1);
    }

    Window::Impl::~Impl()
    {
        XDestroyWindow(m_display, m_window);
        XSetCloseDownMode(m_display, DestroyAll );
        XCloseDisplay(m_display);
        std::cout << "Window destroyed" << std::endl;
    }

    int Window::Impl::GetDesktopWidth() const
    {
        return 0;//WidthOfScreen(m_screen);
    }

    int Window::Impl::GetDesktopHeight() const
    {
        return 0;//HeightOfScreen(m_screen);
    }

    int Window::Impl::GetDesktopBitsPerPixel() const
    {
        auto screen = XDefaultScreenOfDisplay(m_display);
        screen->root_visual->bits_per_rgb;
    }

    int Window::Impl::GetDesktopRefreshRate() const
    {
        auto screen = XDefaultScreenOfDisplay(m_display);
        screen;
    }

    int Window::Impl::GetWidth() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.width;
    }

    int Window::Impl::GetHeight() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.height;
    }

    int Window::Impl::GetX() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.x;
    }

    int Window::Impl::GetY() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.y;
    }

    void Window::Impl::SetSize(int width, int height)
    {
        XWindowChanges v;
        v.width = width;
        v.height = height;
        XConfigureWindow(m_display, m_window, CWWidth | CWHeight, &v);
    }

    void Window::Impl::SetPosition(int x, int y)
    {
        XWindowChanges v;
        v.x = x;
        v.y = y;
        XConfigureWindow(m_display, m_window, CWX | CWY, &v);
    }

    int Window::Impl::DecodeKey(KeySym keysym, int& charKey, bool press)
    {
        bool (*buttons)[256] = System::Keyboard::Instance()->GetKeyStates();    //  TODO: Something better should be here
        bool* m_buttons = *buttons;
        int key;
        switch (keysym)
        {
        case XK_Alt_L:
            m_buttons[(key = PUNK_KEY_LEFT_ALT)] = press;
            break;
        case XK_Alt_R:
            m_buttons[(key = PUNK_KEY_RIGHT_ALT)] = press;
            break;
        case XK_Tab:
            m_buttons[(key = PUNK_KEY_TAB)] = press;
            break;
        case XK_Caps_Lock:
            m_buttons[(key = PUNK_KEY_CAPSLOCK)] = press;
            break;
        case XK_Page_Up:
            m_buttons[(key = PUNK_KEY_PAGE_UP)] = press;
            break;
        case XK_Page_Down:
            m_buttons[(key = PUNK_KEY_PAGE_DOWN)] = press;
            break;
        case XK_Return:
            m_buttons[(key = PUNK_KEY_ENTER)] = press;
            break;
        case XK_Escape:
            m_buttons[(key = PUNK_KEY_ESCAPE)] = press;
            BreakMainLoop();
            break;
        case XK_space:
            charKey = ' ';
            m_buttons[(key = PUNK_KEY_SPACE)] = press;
            break;
        case XK_End:
            m_buttons[(key = PUNK_KEY_END)] = press;
            break;
        case XK_Home:
            m_buttons[(key = PUNK_KEY_HOME)] = press;
            break;
        case XK_Left:
            m_buttons[(key = PUNK_KEY_LEFT)] = press;
            break;
        case XK_Up:
            m_buttons[(key = PUNK_KEY_UP)] = press;
            break;
        case XK_Right:
            m_buttons[(key = PUNK_KEY_RIGHT)] = press;
            break;
        case XK_Down:
            m_buttons[(key = PUNK_KEY_DOWN)] = press;
            break;
        case XK_Insert:
            m_buttons[(key = PUNK_KEY_INSERT)] = press;
            break;
        case XK_Delete:
            m_buttons[(key = PUNK_KEY_DELETE)] = press;
            break;
        case XK_0:
            charKey = '0';
            m_buttons[(key = PUNK_KEY_0)] = press;
            break;
        case XK_1:
            charKey = '1';
            m_buttons[(key = PUNK_KEY_1)] = press;
            break;
        case XK_2:
            charKey = '2';
            m_buttons[(key = PUNK_KEY_2)] = press;
            break;
        case XK_3:
            charKey = '3';
            m_buttons[(key = PUNK_KEY_3)] = press;
            break;
        case XK_4:
            charKey = '4';
            m_buttons[(key = PUNK_KEY_4)] = press;
            break;
        case XK_5:
            charKey = '5';
            m_buttons[(key = PUNK_KEY_5)] = press;
            break;
        case XK_6:
            charKey = '6';
            m_buttons[(key = PUNK_KEY_6)] = press;
            break;
        case XK_7:
            charKey = '7';
            m_buttons[(key = PUNK_KEY_7)] = press;
            break;
        case XK_8:
            charKey = '8';
            m_buttons[(key = PUNK_KEY_8)] = press;
            break;
        case XK_9:
            charKey = '9';
            m_buttons[(key = PUNK_KEY_9)] = press;
            break;
        case XK_A:
            charKey = 'A';
            m_buttons[(key = PUNK_KEY_A)] = press;
            break;
        case XK_a:
            charKey = 'a';
            m_buttons[(key = PUNK_KEY_A)] = press;
            break;
        case XK_B:
            charKey = 'B';
            m_buttons[(key = PUNK_KEY_B)] = press;
            break;
        case XK_b:
            charKey = 'b';
            m_buttons[(key = PUNK_KEY_B)] = press;
            break;
        case XK_C:
            charKey = 'C';
            m_buttons[(key = PUNK_KEY_C)] = press;
            break;
        case XK_c:
            charKey = 'c';
            m_buttons[(key = PUNK_KEY_C)] = press;
            break;
        case XK_D:
            charKey = 'D';
            m_buttons[(key = PUNK_KEY_D)] = press;
            break;
        case XK_d:
            charKey = 'd';
            m_buttons[(key = PUNK_KEY_D)] = press;
            break;
        case XK_E:
            charKey = 'E';
            m_buttons[(key = PUNK_KEY_E)] = press;
            break;
        case XK_e:
            charKey = 'e';
            m_buttons[(key = PUNK_KEY_E)] = press;
            break;
        case XK_F:
            charKey = 'F';
            m_buttons[(key = PUNK_KEY_F)] = press;
            break;
        case XK_f:
            charKey = 'f';
            m_buttons[(key = PUNK_KEY_F)] = press;
            break;
        case XK_G:
            charKey = 'G';
            m_buttons[(key = PUNK_KEY_G)] = press;
            break;
        case XK_g:
            charKey = 'g';
            m_buttons[(key = PUNK_KEY_G)] = press;
            break;
        case XK_H:
            charKey = 'H';
            m_buttons[(key = PUNK_KEY_H)] = press;
            break;
        case XK_h:
            charKey = 'h';
            m_buttons[(key = PUNK_KEY_H)] = press;
            break;
        case XK_I:
            charKey = 'I';
            m_buttons[(key = PUNK_KEY_I)] = press;
            break;
        case XK_i:
            charKey = 'i';
            m_buttons[(key = PUNK_KEY_I)] = press;
            break;
        case XK_J:
            charKey = 'J';
            m_buttons[(key = PUNK_KEY_J)] = press;
            break;
        case XK_j:
            charKey = 'j';
            m_buttons[(key = PUNK_KEY_J)] = press;
            break;
        case XK_K:
            charKey = 'K';
            m_buttons[(key = PUNK_KEY_K)] = press;
            break;
        case XK_k:
            charKey = 'k';
            m_buttons[(key = PUNK_KEY_K)] = press;
            break;
        case XK_L:
            charKey = 'L';
            m_buttons[(key = PUNK_KEY_L)] = press;
            break;
        case XK_l:
            charKey = 'l';
            m_buttons[(key = PUNK_KEY_L)] = press;
            break;
        case XK_M:
            charKey = 'M';
            m_buttons[(key = PUNK_KEY_M)] = press;
            break;
        case XK_m:
            charKey = 'm';
            m_buttons[(key = PUNK_KEY_M)] = press;
            break;
        case XK_N:
            charKey = 'N';
            m_buttons[(key = PUNK_KEY_N)] = press;
            break;
        case XK_n:
            charKey = 'n';
            m_buttons[(key = PUNK_KEY_N)] = press;
            break;
        case XK_O:
            charKey = 'O';
            m_buttons[(key = PUNK_KEY_O)] = press;
            break;
        case XK_o:
            charKey = 'o';
            m_buttons[(key = PUNK_KEY_O)] = press;
            break;
        case XK_P:
            charKey = 'P';
            m_buttons[(key = PUNK_KEY_P)] = press;
            break;
        case XK_p:
            charKey = 'p';
            m_buttons[(key = PUNK_KEY_P)] = press;
            break;
        case XK_Q:
            charKey = 'Q';
            m_buttons[(key = PUNK_KEY_Q)] = press;
            break;
        case XK_q:
            charKey = 'q';
            m_buttons[(key = PUNK_KEY_Q)] = press;
            break;
        case XK_R:
            charKey = 'R';
            m_buttons[(key = PUNK_KEY_R)] = press;
            break;
        case XK_r:
            charKey = 'r';
            m_buttons[(key = PUNK_KEY_R)] = press;
            break;
        case XK_S:
            charKey = 'S';
            m_buttons[(key = PUNK_KEY_S)] = press;
            break;
        case XK_s:
            charKey = 's';
            m_buttons[(key = PUNK_KEY_S)] = press;
            break;
        case XK_T:
            charKey = 'T';
            m_buttons[(key = PUNK_KEY_T)] = press;
            break;
        case XK_t:
            charKey = 't';
            m_buttons[(key = PUNK_KEY_T)] = press;
            break;
        case XK_U:
            charKey = 'U';
            m_buttons[(key = PUNK_KEY_U)] = press;
            break;
        case XK_u:
            charKey = 'u';
            m_buttons[(key = PUNK_KEY_U)] = press;
            break;
        case XK_V:
            charKey = 'V';
            m_buttons[(key = PUNK_KEY_V)] = press;
            break;
        case XK_v:
            charKey = 'v';
            m_buttons[(key = PUNK_KEY_V)] = press;
            break;
        case XK_W:
            charKey = 'W';
            m_buttons[(key = PUNK_KEY_W)] = press;
            break;
        case XK_w:
            charKey = 'w';
            m_buttons[(key = PUNK_KEY_W)] = press;
            break;
        case XK_X:
            charKey = 'X';
            m_buttons[(key = PUNK_KEY_X)] = press;
            break;
        case XK_x:
            charKey = 'x';
            m_buttons[(key = PUNK_KEY_X)] = press;
            break;
        case XK_Y:
            charKey = 'Y';
            m_buttons[(key = PUNK_KEY_Y)] = press;
            break;
        case XK_y:
            charKey = 'y';
            m_buttons[(key = PUNK_KEY_Y)] = press;
            break;
        case XK_Z:
            charKey = 'Z';
            m_buttons[(key = PUNK_KEY_Z)] = press;
            break;
        case XK_z:
            charKey = 'z';
            m_buttons[(key = PUNK_KEY_Z)] = press;
            break;
        case XK_KP_0:
            m_buttons[(key = PUNK_KEY_NUM0)] = press;
            break;
        case XK_KP_1:
            m_buttons[(key = PUNK_KEY_NUM1)] = press;
            break;
        case XK_KP_2:
            m_buttons[(key = PUNK_KEY_NUM2)] = press;
            break;
        case XK_KP_3:
            m_buttons[(key = PUNK_KEY_NUM3)] = press;
            break;
        case XK_KP_4:
            m_buttons[(key = PUNK_KEY_NUM4)] = press;
            break;
        case XK_KP_5:
            m_buttons[(key = PUNK_KEY_NUM5)] = press;
            break;
        case XK_KP_6:
            m_buttons[(key = PUNK_KEY_NUM6)] = press;
            break;
        case XK_KP_7:
            m_buttons[(key = PUNK_KEY_NUM7)] = press;
            break;
        case XK_KP_8:
            m_buttons[(key = PUNK_KEY_NUM8)] = press;
            break;
        case XK_KP_9:
            m_buttons[(key = PUNK_KEY_NUM9)] = press;
            break;
        case XK_F1:
            m_buttons[(key = PUNK_KEY_F1)] = press;
            break;
        case XK_F2:
            m_buttons[(key = PUNK_KEY_F2)] = press;
            break;
        case XK_F3:
            m_buttons[(key = PUNK_KEY_F3)] = press;
            break;
        case XK_F4:
            m_buttons[(key = PUNK_KEY_F4)] = press;
            break;
        case XK_F5:
            m_buttons[(key = PUNK_KEY_F5)] = press;
            break;
        case XK_F6:
            m_buttons[(key = PUNK_KEY_F6)] = press;
            break;
        case XK_F7:
            m_buttons[(key = PUNK_KEY_F7)] = press;
            break;
        case XK_F8:
            m_buttons[(key = PUNK_KEY_F8)] = press;
            break;
        case XK_F9:
            m_buttons[(key = PUNK_KEY_F9)] = press;
            break;
        case XK_F10:
            m_buttons[(key = PUNK_KEY_F10)] = press;
            break;
        case XK_F11:
            m_buttons[(key = PUNK_KEY_F11)] = press;
            break;
        case XK_F12:
            m_buttons[(key = PUNK_KEY_F12)] = press;
            break;
        case XK_Shift_L:
            m_buttons[(key = PUNK_KEY_LEFT_SHIFT)] = press;
            break;
        case XK_Shift_R:
            m_buttons[(key = PUNK_KEY_RIGHT_SHIFT)] = press;
            break;
        case XK_Control_L:
            m_buttons[(key = PUNK_KEY_LEFT_CONTROL)] = press;
            break;
        case XK_Control_R:
            m_buttons[(key = PUNK_KEY_RIGHT_CONTROL)] = press;
            break;
        }
        return key;
    }

    void Window::Impl::OnKeyPressRelease(XKeyEvent* event)
    {
        bool press = event->type == KeyPress;
        int charKey = 0;
        int key = 0;
        KeySym keysym;
        char buffer[1];
        /* It is necessary to convert the keycode to a
* keysym before checking if it is an escape */
        keysym = XLookupKeysym(event, 0);
        if (keysym != NoSymbol)//if (XLookupString(event,buffer,1, &keysym,NULL) == 1)
        {
            key = DecodeKey(keysym, charKey, press);
            if (press)
            {
                if (m_adapter)
                {
                    KeyDownEvent* e = new KeyDownEvent;
                    e->key = key;
                    m_adapter->WndOnKeyDownEvent(e);
                }
            }
            else
            {
                if (m_adapter)
                {
                    KeyUpEvent* e = new KeyUpEvent;
                    e->key = key;
                    m_adapter->WndOnKeyUpEvent(e);
                }
            }

            if (charKey != 0 && press)
            {
                if (m_adapter)
                {
                    KeyCharEvent* e = new KeyCharEvent;
                    e->key = key;
                    m_adapter->WndOnCharEvent(e);
                }
            }
        }
    }

    void Window::Impl::OnMousePressRelease(XEvent* event)
    {
        bool press = event->type == ButtonPress;
        switch (event->xbutton.button)
        {
        case 1: //LEFT
        {
            if (press)
            {
                MouseLeftButtonDownEvent* e = new MouseLeftButtonDownEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;                
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button = true;
                e->middleButton = m_middle_button;
                e->rightButton = m_right_button;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, true);
                MouseLeftButtonDownProc(e);
            }
            else
            {
                MouseLeftButtonUpEvent* e = new MouseLeftButtonUpEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;
                e->leftButton = m_left_button = false;
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button = false;
                e->middleButton = m_middle_button;
                e->rightButton = m_right_button;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, false);
                MouseLeftButtonUpProc(e);
            }
        }
            break;
        case 2: //Middle
            if (press)
            {
                MouseMiddleButtonDownEvent* e = new MouseMiddleButtonDownEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button;
                e->middleButton = m_middle_button = true;
                e->rightButton = m_right_button;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, true);
                MouseMiddleButtonDownProc(e);
            }
            else
            {
                MouseMiddleButtonUpEvent* e = new MouseMiddleButtonUpEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button;
                e->middleButton = m_middle_button = false;
                e->rightButton = m_right_button;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, false);
                MouseMiddleButtonUpProc(e);
            }
            break;
        case 3: //Right
            if (press)
            {
                MouseRightButtonDownEvent* e = new MouseRightButtonDownEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button;
                e->middleButton = m_middle_button;
                e->rightButton = m_right_button = true;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, true);
                MouseRightButtonDownProc(e);
            }
            else
            {
                MouseRightButtonUpEvent* e = new MouseRightButtonUpEvent;
                e->x = event->xbutton.x;
                e->y = GetHeight() - event->xbutton.y;
                e->x_prev = x_prev;
                e->y_prev = y_prev;
                x_prev = e->x;
                y_prev = GetHeight() - event->xbutton.y;
                //event->controlKey = (wParam & MK_CONTROL) != 0;
                e->leftButton = m_left_button;
                e->middleButton = m_middle_button;
                e->rightButton = m_right_button = false;
                //event->shiftButton = (wParam & MK_SHIFT) != 0;
                //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, false);
                MouseRightButtonUpProc(e);

            }
            break;
        case 4: //Whell +
        {
            MouseWheelEvent* e = new MouseWheelEvent;
            e->x = event->xbutton.x;
            e->y = GetHeight() - event->xbutton.y;
            e->delta = 1;
            /*event->controlKey = (bool)(wParam & MK_CONTROL);*/
            e->leftButton = m_left_button;
            e->middleButton = m_middle_button;
            e->rightButton = m_right_button;
/*event->shiftButton = (bool)(wParam & MK_SHIFT);
event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
            MouseWheelProc(e);
        }
            break;
        case 5: //wheel -
        {
            MouseWheelEvent* e = new MouseWheelEvent;
            e->x = event->xbutton.x;
            e->y = GetHeight() - event->xbutton.y;
            e->delta = -1;
            e->leftButton = m_left_button;
            e->middleButton = m_middle_button;
            e->rightButton = m_right_button;
            /*event->controlKey = (bool)(wParam & MK_CONTROL);            
event->shiftButton = (bool)(wParam & MK_SHIFT);
event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
            MouseWheelProc(e);
        }
            break;
        }
    }


    void* PUNK_STDCALL EventThread(void* data)
    {

        out_message() << "Window event thread complete" << std::endl;
    }


    int Window::Impl::Loop()
    {
        Event* e = nullptr;
        XEvent event;

        Timer timer;
        timer.Reset();

        while (!IsClosed())
        {
            while (XPending(m_display))
            {
                XNextEvent(m_display, &event);
                switch (event.type)
                {
                case CreateNotify:
                {
                    if (m_adapter)
                        m_adapter->WndOnCreateEvent();
                    break;
                }
                case ClientMessage:
                {
                    if (event.xclient.data.l[0] = wmDeleteWindow)
                    {
                        BreakMainLoop();
                    }
                }
                    break;
                case ConfigureNotify:
                {
                    WindowResizeEvent* e = new WindowResizeEvent();
                    e->width = event.xconfigure.width;
                    e->height = event.xconfigure.height;
                    WindowResizeProc(e);
                    break;
                }
                case KeyPress:
                case KeyRelease:
                {
                    OnKeyPressRelease((XKeyEvent*)&event);
                    break;
                }
                case MotionNotify:
                {
                    MouseMoveEvent* e = new MouseMoveEvent;
                    e->x_prev = x_prev;
                    e->y_prev = y_prev;
                    e->x = event.xmotion.x;
                    e->y = GetHeight() - event.xmotion.y;
                    x_prev = event.xmotion.x;
                    y_prev = GetHeight() - event.xmotion.y;
                    e->leftButton = m_left_button;
                    e->middleButton = m_middle_button;
                    e->rightButton = m_right_button;
                    /*event->controlKey = (bool)(wParam & MK_CONTROL);
event->leftButton = (bool)(wParam & MK_LBUTTON);
event->middleButton = (bool)(wParam & MK_MBUTTON);
event->rightButton = (bool)(wParam & MK_RBUTTON);
event->shiftButton = (bool)(wParam & MK_SHIFT);
event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
                    //                    m_adapter->WndOnMouseMoveEvent(e);
                    MouseMoveProc(e);
                }
                    break;
                case ButtonPress:
                case ButtonRelease:
                {
                    OnMousePressRelease(&event);
                    break;
                }
                }
            }
            double dt;
            IdleEvent* idle_event = new IdleEvent;
            dt = idle_event->elapsed_time_s = timer.GetElapsedSeconds();
            timer.Reset();
            IdleEventProc(idle_event);
            idle_event = nullptr;
        }

        WindowCloseProc();
        return 0;
    }

    void Window::Impl::BreakMainLoop()
    {
        m_exit_main_loop = true;
    }

    bool Window::Impl::IsClosed()
    {
        bool res = m_exit_main_loop;
        return res;
    }

    void Window::Impl::SetTitle(const string& text)
    {
    }

    const string Window::Impl::GetTitle() const
    {
    }


    void Window::Impl::ShowCursor(bool value)
    {
        static Cursor invisible_cursor = None;
        if (invisible_cursor == None)
        {
            char cursorNoneBits[ 32 ];
            XColor dontCare;
            Pixmap cursorNonePixmap;
            memset( cursorNoneBits, 0, sizeof( cursorNoneBits ) );
            memset( &dontCare, 0, sizeof( dontCare ) );
            cursorNonePixmap = XCreateBitmapFromData( m_display,
                                                      m_window,
                                                      cursorNoneBits, 16, 16 );
            if( cursorNonePixmap != None ) {
                invisible_cursor = XCreatePixmapCursor(m_display,
                                                 cursorNonePixmap, cursorNonePixmap,
                                                  &dontCare, &dontCare, 0, 0 );
                XFreePixmap(m_display, cursorNonePixmap);
            }
        }
        if (value)
        {
            XUndefineCursor(m_display, m_window);
        }
        else
        {
            XDefineCursor(m_display, m_window, invisible_cursor);
        }
    }

    void Window::Impl::Quite()
    {

    }

    void Window::Impl::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        unsigned char rr = Math::Max((int)r - int(255 - a), 0);
        unsigned char gg = Math::Max((int)g - int(255 - a), 0);
        unsigned char bb = Math::Max((int)b - int(255 - a), 0);
    }

    void Window::Impl::DrawLine(int x1, int y1, int x2, int y2)
    {
    }

    Window::Window(WindowAdapter* adapter, const WindowDesc& desc)
        : impl(new Impl(adapter, desc))
    {}

    void Window::SetTitle(const string& text)
    {
        impl->SetTitle(text);
    }

    const string Window::GetTitle() const
    {
        return impl->GetTitle();
    }

    void Window::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        impl->DrawPixel(x, y, r, g, b, a);
    }

    int Window::GetDesktopBitsPerPixel() const
    {
        return impl->GetDesktopBitsPerPixel();
    }

    int Window::GetDesktopHeight() const
    {
        return impl->GetDesktopHeight();
    }

    int Window::GetDesktopRefreshRate() const
    {
        return impl->GetDesktopRefreshRate();
    }

    int Window::GetDesktopWidth() const
    {
        return impl->GetDesktopWidth();
    }

    void Window::BreakMainLoop()
    {
        impl->BreakMainLoop();
    }

    int Window::Loop()
    {
        return impl->Loop();
    }

    void Window::DrawLine(int x1, int y1, int x2, int y2)
    {
        impl->DrawLine(x1, y1, x2, y2);
    }

    void Window::Quite()
    {
        impl->Quite();
    }

    void Window::SetSize(int width, int height)
    {
        impl->SetSize(width, height);
    }

    void Window::SetPosition(int x, int y)
    {
        impl->SetPosition(x, y);
    }

    int Window::GetX() const
    {
        return impl->GetX();
    }

    int Window::GetY() const
    {
        return impl->GetY();
    }

    int Window::GetWidth() const
    {
        return impl->GetWidth();
    }

    int Window::GetHeight() const
    {
        return impl->GetHeight();
    }

    Window::~Window()
    {
        delete impl;
        impl = nullptr;
    }

    Display* Window::GetDisplay()
    {
        return impl->m_display;
    }

    void Window::SetDisplay(Display *display)
    {
        if (impl->m_display)
        {
            //XDestroyWindow(impl->m_display, impl->m_window);
            //XCloseDisplay(impl->m_display);
            impl->m_display = 0;
            impl->m_window = 0;
        }
        impl->m_display = display;
    }

    void Window::SetWindow(::Window value)
    {
        if (impl->m_window)
            XDestroyWindow(impl->m_display, impl->m_window);
        impl->m_window = value;
        XSetWMProtocols(impl->m_display, impl->m_window, &impl->wmDeleteWindow, 1);
    }

    ::Window Window::GetWindow()
    {
        return impl->m_window;
    }

    void Window::Impl::MouseMoveProc(Event* e)
    {
        if (Mouse::Instance()->IsLocked())
        {
            MouseMoveEvent* event = (MouseMoveEvent*)e;
            int w = GetWidth();
            int h = GetHeight();
            int w2 = w / 2;
            int h2 = h / 2;
            int w4 = w2 / 2;
            int h4 = h2 / 2;
            if (abs(event->x - w2) > w4 || abs(event->y - h2) > h4)
            {
                x_prev = w2;
                y_prev = h2;
                x = w2;
                y = h2;
                event->x = event->x_prev = w2;
                event->y = event->y_prev = h2;
                XWarpPointer(m_display, m_window, m_window, 0, 0, 0, 0, w2, h2);
            }
        }
        if (m_adapter)
        {
            m_adapter->WndOnMouseMoveEvent((MouseMoveEvent*)e);
        }
        else
        {
            delete (MouseMoveEvent*)e;
        }
    }

    void Window::Impl::KeyDownProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnKeyDownEvent((KeyDownEvent*)e);
        }
        else
        {
            delete (KeyDownEvent*)e;
        }
    }

    void Window::Impl::MouseWheelProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseWheelEvent((MouseWheelEvent*)e);
        }
        else
        {
            delete (MouseWheelEvent*)e;
        }
    }

    void Window::Impl::KeyUpProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnKeyUpEvent((KeyUpEvent*)e);
        }
        else
        {
            delete (KeyUpEvent*)e;
        }
    }

    void Window::Impl::KeyCharProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnCharEvent((KeyCharEvent*)e);
        }
        else
        {
            delete (KeyCharEvent*)e;
        }
    }

    void Window::Impl::MouseLeftButtonDownProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseLeftButtonDownEvent((MouseLeftButtonDownEvent*)e);
        }
        else
        {
            delete (MouseLeftButtonDownEvent*)e;
        }
    }

    void Window::Impl::MouseLeftButtonUpProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseLeftButtonUpEvent((MouseLeftButtonUpEvent*)e);
        }
        else
        {
            delete (MouseLeftButtonUpEvent*)e;
        }
    }
    void Window::Impl::MouseRightButtonDownProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseRightButtonDownEvent((MouseRightButtonDownEvent*)e);
        }
        else
        {
            delete (MouseRightButtonDownEvent*)e;
        }
    }
    void Window::Impl::MouseRightButtonUpProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseRightButtonUpEvent((MouseRightButtonUpEvent*)e);
        }
        else
        {
            delete (MouseRightButtonUpEvent*)e;
        }
    }
    void Window::Impl::MouseMiddleButtonDownProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseMiddleButtonDownEvent((MouseMiddleButtonDownEvent*)e);
        }
        else
        {
            delete (MouseMiddleButtonDownEvent*)e;
        }
    }
    void Window::Impl::MouseMiddleButtonUpProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseMiddleButtonUpEvent((MouseMiddleButtonUpEvent*)e);
        }
        else
        {
            delete (MouseMiddleButtonUpEvent*)e;
        }
    }
    void Window::Impl::WindowResizeProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnResizeEvent((WindowResizeEvent*)e);
        }
        else
        {
            delete (WindowResizeEvent*)e;
        }
    }

    void Window::Impl::MouseEnterProc(Event* e)
    {
        delete e;
    }

    void Window::Impl::MouseLeaveProc(Event* e)
    {
        delete e;
    }

    void Window::Impl::SetFocusedProc(Event* e)
    {
        delete e;
    }

    void Window::Impl::SetUnfocusedProc(Event* e)
    {
        delete e;
    }

    void Window::Impl::KeyWcharProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnWideCharEvent((KeyWCharEvent*)e);
        }
        else
        {
            delete (KeyWCharEvent*)e;
        }
    }

    void Window::Impl::MouseHooverProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnMouseHooverEvent((MouseHooverEvent*)e);
        }
        else
        {
            delete (MouseHooverEvent*)e;
        }
    }

    void Window::Impl::IdleEventProc(Event* e)
    {
        if (m_adapter)
        {
            m_adapter->WndOnIdleEvent((IdleEvent*)e);
        }
        else
        {
            delete (IdleEvent*)e;
        }
    }

    void Window::Impl::WindowCloseProc()
    {
        if (m_adapter)
        {
            m_adapter->WndOnDestroyEvent();
        }
    }

    void Window::ShowCursor(bool value)
    {
        impl->ShowCursor(value);
    }
}

#endif  //  linux
