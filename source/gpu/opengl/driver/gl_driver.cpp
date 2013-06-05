
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <dlfcn.h>
#endif

#include "../../gpu_config.h"
#include "../../../config.h"
#include "../../../system/smart_pointers/module.h"
#include "../../../system/module.h"
#include "../gl/module.h"
#include "../error/module.h"
#include "gl_driver.h"
#include "../../../math/vec4.h"
#include "../../common/frame.h"

namespace GPU
{
using namespace OpenGL;

void* GetGPUProcAddress(const char* name)
{
#ifdef _WIN32
    void* res = (void*)wglGetProcAddress(name);
    if (res != 0)
        return res;
    HMODULE lib = LoadLibrary(L"OpenGL32.dll");
    res = (void*)::GetProcAddress(lib, name);
    FreeLibrary(lib);
    GetLastError();
    return res;
#elif defined __gnu_linux__
    if (strcmp(name, "glXGetProcAddress") == 0)
    {
        void* handle = dlopen("libGL.so", RTLD_NOW);
        void* res = dlsym(handle, name);
        return res;
    }
    else
    {
        if (!glXGetProcAddress)
        {
            void* handle = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_NOW);
            void* res = dlsym(handle, "glXGetProcAddress");
            return res;
        }
        void* res = (void*)glXGetProcAddress((const GLubyte*)name);
        if (res != 0)
            return res;
        return nullptr;
    }
#endif
}


VideoDriverImpl::VideoDriverImpl(VideoDriver* driver)
    : m_driver(driver)
{}

VideoDriverImpl::~VideoDriverImpl()
{
    try
    {
        Shutdown();
    }
    catch(...)
    {
    }
}

void VideoDriverImpl::SetFontBuilder(Utility::FontBuilder *value)
{
    m_font_builder = value;
}

Utility::FontBuilder* VideoDriverImpl::GetFontBuilder()
{
    return m_font_builder;
}

void VideoDriverImpl::SetFullScreen(bool flag)
{
    m_desc.config.fullscreen = flag;
#ifdef _WIN32
    if (flag)
    {
        SetWindowLong(*m_desc.window, GWL_STYLE, WS_POPUP);
        SetWindowLong(*m_desc.window, GWL_EXSTYLE, WS_EX_APPWINDOW);

        out_message() << L"Fullscreen mode..." << std::endl;
        DEVMODE mode;
        ZeroMemory(&mode, sizeof(mode));
        mode.dmSize = sizeof(mode);
        mode.dmPelsWidth = m_desc.config.view_width;
        mode.dmPelsHeight = m_desc.config.view_height;
        mode.dmBitsPerPel = m_desc.config.bits_per_pixel;
        mode.dmDisplayFrequency = m_desc.config.refresh_rate;
        mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        SetWindowPos(*m_desc.window, 0, 0, 0, m_desc.config.view_width, m_desc.config.view_height, SWP_SHOWWINDOW);

        LONG code;
        if ((code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN)) != DISP_CHANGE_SUCCESSFUL)
        {
            out_error() << L"Can't change display settings " << std::endl;
            return;
        }
    }
    else
    {
        SetWindowLong(*m_desc.window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowLong(*m_desc.window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

        out_message() << L"Window mode..." << std::endl;
        m_desc.window->SetPosition(m_desc.config.view_left, m_desc.config.view_top);
        m_desc.window->SetSize(m_desc.config.view_width, m_desc.config.view_height);
    }

    ShowWindow(*m_desc.window, SW_SHOW);
    SetFocus(*m_desc.window);
#endif
}

bool VideoDriverImpl::Start(const VideoDriverDesc& desc)
{
    m_desc = desc;
    out_message() << L"Initializing OpenGL..." << std::endl;

#ifdef _WIN32
    HDC deviceContext = ::GetDC((*m_desc.window));

    SetFullScreen(m_desc.config.fullscreen);

    int pixelFormat;
    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(pfd),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        (BYTE)m_desc.config.bits_per_pixel,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    if (!(pixelFormat = ChoosePixelFormat(deviceContext, &pfd)))
    {
        out_error() << L"Can't choose pixel format" << std::endl;
        return false;
    }

    if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
    {
        out_error() << L"Can't set pixel format" << std::endl;
        return false;
    }

    HGLRC tempContext;
    if ((tempContext = wglCreateContext(deviceContext)) == NULL)
    {
        out_error() << L"Can't create temporary opengl context" << std::endl;
        return false;
    }

    if (!wglMakeCurrent(deviceContext, tempContext))
    {
        out_error() << L"Can't set created context to be current" << std::endl;
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

    //		int forward = 0;
    int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                        WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
                        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
                        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
                       };

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetGPUProcAddress("wglCreateContextAttribsARB");

    if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
    {
        out_error() << L"Can't create opengl 3.x context" << std::endl;
        return false;
    }

    if (!wglMakeCurrent(deviceContext, m_opengl_context))
    {
        out_error() << L"Can't set opengl 3.x context to be current" << std::endl;
        return false;
    }

    wglDeleteContext(tempContext);

    InitExtensions(GetGPUProcAddress);

    GLint t;

    out_message() << System::string("\tRenderer: {0} ").arg((const char*)glGetString(GL_RENDERER)) << std::endl;
    out_message() << System::string("\tVendor: {0} ").arg((const char*)glGetString(GL_VENDOR)) << std::endl;
    out_message() << System::string("\tVersion: {0}").arg((const char*)glGetString(GL_VERSION)) << std::endl;
    out_message() << System::string("\tGLSL version: {0}").arg((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
    out_message() << System::string("\tMax vertex attribs: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
    out_message() << System::string("\tMax vertex uniform components: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
    out_message() << System::string("\tMax varying floats: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &t);
    out_message() << L"\tMax 3D texture size: " << t << std::endl;
    glGetIntegerv(GL_MAX_CLIP_DISTANCES, &t);
    out_message() << L"\tMax clip distances: " << t << std::endl;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &t);
    out_message() << L"\tMax combined texture image units: " << t << std::endl;
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &t);
    out_message() << L"\tMax cube map texture size: " << t << std::endl;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &t);
    out_message() << L"\tMax draw buffers: " << t << std::endl;
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &t);
    out_message() << L"\tMax elements indices: " << t << std::endl;
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &t);
    out_message() << L"\tMax elements vertices: " << t << std::endl;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);
    out_message() << L"\tMax texture image units in FS: " << t << std::endl;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &t);
    out_message() << L"\tMax render buffer size: " << t << std::endl;


    wglSwapIntervalEXT(0);

    const unsigned char* sv= glGetString(GL_SHADING_LANGUAGE_VERSION);
    m_shader_version = ((int)(sv[0]-'0'))*100;
    m_shader_version += ((int)(sv[2]-'0'))*10;
    m_shader_version += ((int)(sv[3]-'0'));

    sv = glGetString(GL_VERSION);
    m_opengl_version = ((int)(sv[0]-'0'))*100;
    m_opengl_version += ((int)(sv[2]-'0'))*10;
    m_opengl_version += ((int)(sv[3]-'0'));

    int profile;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
    if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
        out_message() << L"\tCore profile selected" << std::endl;
    if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
        out_message() << L"\tCompatible profile selected" << std::endl;

    m_desc.event_manager->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &VideoDriverImpl::OnResize));
    m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &VideoDriverImpl::OnKeyDown));

#elif defined __gnu_linux__

    InitGlxFunctions();

    auto display = XOpenDisplay(NULL);
    if (display == NULL)
        throw System::PunkException("XWindow: can't open display");

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

    int glx_major = 0, glx_minor = 0;

    if (!glXQueryVersion(display, &glx_minor, &glx_major) ||
            (( glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
    {
        printf("GLX VERSION: %d.%d\n", glx_major, glx_minor);
        throw System::PunkException("Bad glx version");
    }

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display),
                                         visual_attribs, &fbcount);

    if (!fbc)
    {
        printf("failed to retrieve framebuffer config\n");
        throw System::PunkException("unable to create framebuffer");
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
    Colormap colorMap;
    XSetWindowAttributes swa;
    swa.colormap = colorMap = XCreateColormap( display,
                                               RootWindow( display, vi->screen ),
                                               vi->visual, AllocNone );
    swa.background_pixmap = None ;
    swa.border_pixel      = 0;
    swa.event_mask        = KeyPressMask | PointerMotionMask | StructureNotifyMask
            | ButtonPressMask;

    printf( "Creating window\n" );
    auto window = XCreateWindow( display,
                                 RootWindow( display, vi->screen ),
                                 0, 0, 800, 600, 0, vi->depth, InputOutput,
                                 vi->visual,
                                 CWBorderPixel|CWColormap|CWEventMask, &swa );
    if ( !window )
    {
        printf( "Failed to create window.\n" );
        throw System::PunkException("Can't create XWindow");
    }

    // Done with the visual info data
    XFree( vi );

    XStoreName( display, window, "GL 2.0 Window" );

    printf( "Mapping window\n" );
    XMapWindow(display, window);
    printf( "Ok...\n");
    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString( display, DefaultScreen( display ) );

    printf("Extesion string is %s\n", glxExts);
    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    printf("glXGetProcAddress %p\n", glXGetProcAddress);
    printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);

    printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);

    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    //        if ( !IsSupported("GLX_ARB_create_context") ||
    //             !glXCreateContextAttribsARB )
    //        {
    //            printf( "glXCreateContextAttribsARB() not found"
    //                    " ... using old-style GLX context\n" );
    //            printf("glXCreateNewContext address is %p\n", glXCreateContext);
    //            ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
    //        }

    // If it does, try to get a GL 3.0 context!
    //else
    {
        int context_attribs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3, 0,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3, 0,
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, 0
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
        throw System::PunkException("Can't create glx context");
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

    m_desc.window->SetDisplay(display);
    m_desc.window->SetWindow(window);
    printf( "Window created \n");
#endif

    InitExtensions();


    GLint t;

    out_message() << "\tRenderer: " << (const char*)glGetString(GL_RENDERER) << std::endl;
    out_message() << "\tVendor: " << (const char*)glGetString(GL_VENDOR) << std::endl;
    out_message() << "\tVersion: "  << (const char*)glGetString(GL_VERSION) << std::endl;
    out_message() << "\tGLSL version: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
    out_message() << System::string("\tMax vertex attribs: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
    out_message() << System::string("\tMax vertex uniform components: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
    out_message() << System::string("\tMax varying floats: {0}").arg(t) << std::endl;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &t);
    out_message() << "\tMax 3D texture size: " << t << std::endl;
    glGetIntegerv(GL_MAX_CLIP_DISTANCES, &t);
    out_message() << "\tMax clip distances: " << t << std::endl;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &t);
    out_message() << "\tMax combined texture image units: " << t << std::endl;
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &t);
    out_message() << "\tMax cube map texture size: " << t << std::endl;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &t);
    out_message() << "\tMax draw buffers: " << t << std::endl;
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &t);
    out_message() << "\tMax elements indices: " << t << std::endl;
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &t);
    out_message() << "\tMax elements vertices: " << t << std::endl;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);
    out_message() << "\tMax texture image units in FS: " << t << std::endl;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &t);
    out_message() << "\tMax render buffer size: " << t << std::endl;

    const unsigned char* sv= glGetString(GL_SHADING_LANGUAGE_VERSION);

    out_message() << "GLSL version: " << (const char*)sv << std::endl;
    m_shader_version = ((int)(sv[0]-'0'))*100;
    m_shader_version += ((int)(sv[2]-'0'))*10;
    m_shader_version += ((int)(sv[3]-'0'));

    sv = glGetString(GL_VERSION);
    out_message() << "GL version: " << (const char*)sv << std::endl;
    m_opengl_version = ((int)(sv[0]-'0'))*100;
    m_opengl_version += ((int)(sv[2]-'0'))*10;
    m_opengl_version += ((int)(sv[3]-'0'));

    int profile;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
    if (profile & GLX_CONTEXT_CORE_PROFILE_BIT_ARB)
        out_message() << "\tCore profile selected" << std::endl;
    if (profile & GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
        out_message() << "\tCompatible profile selected" << std::endl;

    m_memory = new VideoMemory;

    return true;
}

void VideoDriverImpl::Restart()
{
    Shutdown();
    Start(m_desc);
}

void VideoDriverImpl::Shutdown()
{
    out_message() << L"Clear video memory" << std::endl;
    delete m_memory;
    out_message() << L"Destroying video driver..." << std::endl;
#ifdef _WIN32
    ChangeDisplaySettings(NULL, 0);
    wglMakeCurrent(::GetDC(*m_desc.window), NULL);
    wglDeleteContext(m_opengl_context);
#elif defined __gnu_linux__
#endif
    out_message() << L"Video driver destroyed..." << std::endl;
}

void VideoDriverImpl::SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer)
{
    if (color_buffer || depth_buffer)
    {
        m_rt.reset(new RenderTargetTexture(color_buffer, depth_buffer));
    }
    else
    {
        m_rt.reset(new RenderTargetBackBuffer());
    }
}

void VideoDriverImpl::SetClearColor(const Math::vec4& color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
}

void VideoDriverImpl::SetClearDepth(float value)
{
    glClearDepth(value);
}

void VideoDriverImpl::Clear(bool color, bool depth, bool stencil)
{
    GLbitfield b = 0;

    if (color)
        b |= GL_COLOR_BUFFER_BIT;
    if (depth)
        b |= GL_DEPTH_BUFFER_BIT;
    if (stencil)
        b |= GL_STENCIL_BUFFER_BIT;

    glClear(b);
    ValidateOpenGL(L"Unable to clear buffer");
}

void VideoDriverImpl::SwapBuffers()
{
#ifdef _WIN32
    if (!::SwapBuffers(::GetDC(*m_desc.window)))
        out_error() << "Swap buffer failed" << std::endl;
#elif defined __gnu_linux__
#endif
}

void VideoDriverImpl::OnResize(System::Event* e)
{
    System::WindowResizeEvent* event = dynamic_cast<System::WindowResizeEvent*>(e);
    if (!event)
        throw OpenGLInvalidValueException(L"Can't understand event");
    glViewport(0, 0, event->width, event->height);
}

void VideoDriverImpl::SetViewport(float x, float y, float width, float height)
{
    if (glViewport)
        glViewport(x, y, width, height);
}

void VideoDriverImpl::OnKeyDown(System::Event* e)
{
    System::KeyDownEvent* event = dynamic_cast<System::KeyDownEvent*>(e);
    if (!event)
    {
        out_error() << L"Unexpected event recieved" << std::endl;
        return;
    }

    if (event->key == System::PUNK_KEY_ENTER)
    {
        if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_ALT))
            SetFullScreen(!m_desc.config.fullscreen);
    }
}

OpenGL::VideoMemory* VideoDriverImpl::GetVideoMemory()
{
    return m_memory;
}

const OpenGL::VideoMemory* VideoDriverImpl::GetVideoMemory() const
{
    return m_memory;
}

System::Window* VideoDriverImpl::GetWindow() { return m_desc.window; }

VideoDriver::VideoDriver()
    : impl(new VideoDriverImpl(this))
{}

const Config& VideoDriverImpl::GetConfig() const
{
    return m_desc.config;
}

#ifdef __gnu_linux__
void VideoDriverImpl::InitGlxFunctions()
{
    glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)GetGPUProcAddress("glXGetProcAddress");
    glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)GetGPUProcAddress("glXCreateContextAttribsARB");
    glXQueryVersion = (PFNGLXQUERYVERSIONPROC)GetGPUProcAddress("glXQueryVersion");
    glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC)GetGPUProcAddress("glXChooseFBConfig");
    glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)GetGPUProcAddress("glXGetVisualFromFBConfig");
    glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)GetGPUProcAddress("glXGetFBConfigAttrib");
    glXQueryExtensionsString = (PFNGLXQUERYEXTENSIONSSTRINGPROC)GetGPUProcAddress("glXQueryExtensionsString");
    glXCreateContext = (PFNGLXCREATECONTEXTPROC)GetGPUProcAddress("glXCreateContext");
    glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)GetGPUProcAddress("glXCreateNewContext");
    glXIsDirect = (PFNGLXISDIRECTPROC)GetGPUProcAddress("glXIsDirect");
    glXMakeCurrent = (PFNGLXMAKECURRENTPROX)GetGPUProcAddress("glXMakeCurrent");
}
#endif

bool VideoDriverImpl::IsSupported(const char* extension)
{
#ifdef _WIN32
    const char* allWgl = wglGetExtensionsStringARB(*m_desc.window);
#elif defined __gnu_linux__
    const char* allWgl = glXQueryExtensionsString(GetWindow()->GetDisplay(), GetWindow()->GetWindow());
#endif
    int num;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num);
    const char* ptr;
    const char* start;
    start = allWgl;
    for (int i = 0; i < num; i++)
    {
        const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
        if ((ptr = strstr(extension, ext)) != NULL)
        {
            const char* end = ptr + strlen(extension);
            if (isspace(*end) || *end == '\0')
            {
                out_message() << System::string("[Video] {0} is supported").arg(extension) << std::endl;
                return true;
            }
        }
    }
    out_warning() << System::string("[Video] {0} is not supported").arg(extension) << std::endl;
    return false;
}

VideoDriver::~VideoDriver()
{
    delete impl;
    impl = nullptr;
}

void VideoDriver::SetFontBuilder(Utility::FontBuilder *value)
{
    impl->SetFontBuilder(value);
}

Utility::FontBuilder* VideoDriver::GetFontBuilder()
{
    return impl->GetFontBuilder();
}

void VideoDriver::SetFullScreen(bool flag)
{
    impl->SetFullScreen(flag);
}

bool VideoDriver::Start(const VideoDriverDesc& desc)
{
    return impl->Start(desc);
}

void VideoDriver::Restart()
{
    return impl->Restart();
}

void VideoDriver::Shutdown()
{
    impl->Shutdown();
}

Frame* VideoDriver::BeginFrame()
{
    Frame* frame = new Frame(this);
    return frame;
}

void VideoDriver::EndFrame(Frame* value)
{
    delete value;
}

System::Window* VideoDriver::GetWindow()
{
    return impl->GetWindow();
}

void VideoDriver::SetViewport(float x, float y, float width, float height)
{
    impl->SetViewport(x, y, width, height);
}

void VideoDriver::SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer)
{
    impl->SetRenderTarget(color_buffer, depth_buffer);
}

void VideoDriver::SetClearColor(const Math::vec4& color)
{
    impl->SetClearColor(color);
}

void VideoDriver::SetClearDepth(float value)
{
    impl->SetClearDepth(value);
}

void VideoDriver::Clear(bool color, bool depth, bool stencil)
{
    impl->Clear(color, depth, stencil);
}

void VideoDriver::SwapBuffers()
{
    impl->SwapBuffers();
}

const Config& VideoDriver::GetConfig() const
{
    return impl->GetConfig();
}

void VideoDriverImpl::InitExtensions()
{

#ifdef _WIN32
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetGPUProcAddress("wglGetExtensionsStringARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)GetGPUProcAddress("wglSwapIntervalEXT");
#endif
    glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetGPUProcAddress("glTexParameterf");
    glBindTexture = (PFNGLBINDTEXTUREPROC)GetGPUProcAddress("glBindTexture");
    glGetIntegerv = (PFNGLGETINTEGERVPROC)GetGPUProcAddress("glGetIntegerv");
    glGetStringi = (PFNGLGETSTRINGIPROC)GetGPUProcAddress("glGetStringi");
    glGetError = (PFNGLGETERRORPROC)GetGPUProcAddress("glGetError");
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)GetGPUProcAddress("glDrawRangeElements");
    glViewport = (PFNGLVIEWPORTPROC)GetGPUProcAddress("glViewport");
    glClearColor = (PFNGLCLEARCOLORPROC)GetGPUProcAddress("glClearColor");
    glEnable = (PFNGLENABLEPROC)GetGPUProcAddress("glEnable");
    glDisable = (PFNGLDISABLEPROC)GetGPUProcAddress("glDisable");
    glReadPixels = (PFNGLREADPIXELSPROC)GetGPUProcAddress("glReadPixels");
    glGetString = (PFNGLGETSTRINGPROC)GetGPUProcAddress("glGetString");
    glGenTextures = (PFNGLGENTEXTURESPROC)GetGPUProcAddress("glGenTextures");
    glBindTexture = (PFNGLBINDTEXTUREPROC)GetGPUProcAddress("glBindTexture");
    glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetGPUProcAddress("glTexParameterf");
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetGPUProcAddress("glTexParameterfv");
    glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetGPUProcAddress("glTexImage2D");
    glFramebufferTexture2D= (PFNGLFRAMEBUFFERTEXTURE2DPROC)GetGPUProcAddress("glFramebufferTexture2D");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetGPUProcAddress("glDeleteTextures");
    glDrawBuffer = (PFNGLDRAWBUFFERPROC)GetGPUProcAddress("glDrawBuffer");
    glReadBuffer = (PFNGLREADBUFFERPROC)GetGPUProcAddress("glReadBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC)GetGPUProcAddress("glBufferData");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC)GetGPUProcAddress("glBufferSubData");
    glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)GetGPUProcAddress("glGetBufferSubData");
    glGenBuffers = (PFNGLGENBUFFERSPROC)GetGPUProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)GetGPUProcAddress("glBindBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)GetGPUProcAddress("glDeleteBuffers");
    glMapBuffer = (PFNGLMAPBUFFERPROC)GetGPUProcAddress("glMapBuffer");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)GetGPUProcAddress("glUnmapBuffer");
    glIsBuffer = (PFNGLISBUFFERPROC)GetGPUProcAddress("glIsBuffer");
    glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)GetGPUProcAddress("glIsRenderbuffer");
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)GetGPUProcAddress("glBindRenderbuffer");
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)GetGPUProcAddress("glDeleteRenderbuffers");
    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)GetGPUProcAddress("glGenRenderbuffers");
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)GetGPUProcAddress("glRenderbufferStorage");
    glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)GetGPUProcAddress("glGetRenderbufferParameteriv");
    glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)GetGPUProcAddress("glIsFramebuffer");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)GetGPUProcAddress("glBindFramebuffer");
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)GetGPUProcAddress("glDeleteFramebuffers");
    glGenFramebuffers =  (PFNGLGENFRAMEBUFFERSPROC)GetGPUProcAddress("glGenFramebuffers");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)GetGPUProcAddress("glCheckFramebufferStatus");
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)GetGPUProcAddress("glFramebufferRenderbuffer");
    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)GetGPUProcAddress("glGetFramebufferAttachmentParameteriv");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetGPUProcAddress("glGenerateMipmap");;
    glCreateShader = (PFNGLCREATESHADERPROC)GetGPUProcAddress("glCreateShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetGPUProcAddress("glCreateProgram");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)GetGPUProcAddress("glDeleteProgram");
    glDeleteShader = (PFNGLDELETESHADERPROC)GetGPUProcAddress("glDeleteShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)GetGPUProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)GetGPUProcAddress("glCompileShader");
    glAttachShader = (PFNGLATTACHSHADERPROC)GetGPUProcAddress("glAttachShader");
    glDetachShader = (PFNGLDETACHSHADERPROC)GetGPUProcAddress("glDetachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)GetGPUProcAddress("glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC)GetGPUProcAddress("glUseProgram");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GetGPUProcAddress("glValidateProgram");
    glUniform1f = (PFNGLUNIFORM1FPROC)GetGPUProcAddress("glUniform1f");
    glUniform1fv = (PFNGLUNIFORM1FVPROC )GetGPUProcAddress("glUniform1fv");
    glUniform1i = (PFNGLUNIFORM1IPROC )GetGPUProcAddress("glUniform1i");
    glUniform1iv = (PFNGLUNIFORM1IVPROC )GetGPUProcAddress("glUniform1iv");
    glUniform2f = (PFNGLUNIFORM2FPROC )GetGPUProcAddress("glUniform2f");
    glUniform2fv = (PFNGLUNIFORM2FVPROC )GetGPUProcAddress("glUniform2fv");
    glUniform2iv = (PFNGLUNIFORM2IVPROC )GetGPUProcAddress("glUniform2iv");
    glUniform3f = (PFNGLUNIFORM3FPROC )GetGPUProcAddress("glUniform3f");
    glUniform3iv = (PFNGLUNIFORM3IVPROC )GetGPUProcAddress("glUniform3iv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC )GetGPUProcAddress("glUniform3fv");
    glUniform3i = (PFNGLUNIFORM3IPROC )GetGPUProcAddress("glUniform3i");
    glUniform4f = (PFNGLUNIFORM4FPROC )GetGPUProcAddress("glUniform4f");
    glUniform4iv = (PFNGLUNIFORM4IVPROC )GetGPUProcAddress("glUniform4iv");
    glUniform4fv = (PFNGLUNIFORM4FVPROC )GetGPUProcAddress("glUniform4fv");
    glUniform4i = (PFNGLUNIFORM4IPROC )GetGPUProcAddress("glUniform4i");
    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC )GetGPUProcAddress("glGetActiveUniform");
    glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)GetGPUProcAddress("glGetAttachedShaders");
    glGetShaderSource = (PFNGLGETSHADERSOURCEPROC )GetGPUProcAddress("glGetShaderSource");
    glGetUniformfv = (PFNGLGETUNIFORMFVPROC )GetGPUProcAddress("glGetUniformfv");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC )GetGPUProcAddress("glGetUniformLocation");
    glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)GetGPUProcAddress("glVertexAttrib1d");
    glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)GetGPUProcAddress("glVertexAttrib1dv");
    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)GetGPUProcAddress("glVertexAttrib1f");
    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)GetGPUProcAddress("glVertexAttrib1fv");
    glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC )GetGPUProcAddress("glVertexAttrib1s");
    glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC )GetGPUProcAddress("glVertexAttrib1sv");
    glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC )GetGPUProcAddress("glVertexAttrib2d");
    glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC )GetGPUProcAddress("glVertexAttrib2dv");
    glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC )GetGPUProcAddress("glVertexAttrib2f");
    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC )GetGPUProcAddress("glVertexAttrib2fv");
    glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC )GetGPUProcAddress("glVertexAttrib2s");
    glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC )GetGPUProcAddress("glVertexAttrib2sv");
    glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC )GetGPUProcAddress("glVertexAttrib3d");
    glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC )GetGPUProcAddress("glVertexAttrib3dv");
    glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC )GetGPUProcAddress("glVertexAttrib3f");
    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC )GetGPUProcAddress("glVertexAttrib3fv");
    glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC )GetGPUProcAddress("glVertexAttrib3s");
    glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC )GetGPUProcAddress("glVertexAttrib3sv");
    glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC )GetGPUProcAddress("glVertexAttrib4d");
    glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC )GetGPUProcAddress("glVertexAttrib4dv");
    glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC )GetGPUProcAddress("glVertexAttrib4f");
    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC )GetGPUProcAddress("glVertexAttrib4fv");
    glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC )GetGPUProcAddress("glVertexAttrib4s");
    glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC )GetGPUProcAddress("glVertexAttrib4sv");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC )GetGPUProcAddress("glVertexAttribPointer");
    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC )GetGPUProcAddress("glBindAttribLocation");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC )GetGPUProcAddress("glEnableVertexAttribArray");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC )GetGPUProcAddress("glDisableVertexAttribArray");
    glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC )GetGPUProcAddress("glGetVertexAttribdv");
    glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC )GetGPUProcAddress("glGetVertexAttribfv");
    glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC )GetGPUProcAddress("glGetVertexAttribiv");
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC )GetGPUProcAddress("glGetVertexAttribPointerv");
    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC )GetGPUProcAddress("glGetActiveAttrib");
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)GetGPUProcAddress("glUniformMatrix2fv");
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)GetGPUProcAddress("glUniformMatrix3fv");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)GetGPUProcAddress("glUniformMatrix4fv");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GetGPUProcAddress("glGetAttribLocation");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)GetGPUProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetGPUProcAddress("glGetShaderInfoLog");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetGPUProcAddress("glGetProgramiv");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetGPUProcAddress("glGenVertexArrays");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)GetGPUProcAddress("glDeleteVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetGPUProcAddress("glBindVertexArray");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)GetGPUProcAddress("glDrawArrays");
    glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)GetGPUProcAddress("glDrawArraysIndirect");
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)GetGPUProcAddress("glDrawArraysInstanced");
    glDrawElements = (PFNGLDRAWELEMENTSPROC)GetGPUProcAddress("glDrawElements");
    glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)GetGPUProcAddress("glDrawElementsIndirect");
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)GetGPUProcAddress("glDrawElementsInstanced");
    glClear = (PFNGLCLEARPROC)GetGPUProcAddress("glClear");
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)GetGPUProcAddress("glCompressedTexImage2D");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC)GetGPUProcAddress("glActiveTexture");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetGPUProcAddress("glGetProgramiv");
    glBlendFunc = (PFNGLBLENDFUNCPROC)GetGPUProcAddress("glBlendFunc");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC)GetGPUProcAddress("glBlendEquation");
    glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)GetGPUProcAddress("glBlendEquationi");
    glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)GetGPUProcAddress("glBlendEquationSeparate");
    glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)GetGPUProcAddress("glBlendEquationSeparatei");
    glEnablei = (PFNGLENABLEIPROC)GetGPUProcAddress("glEnablei");
    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)GetGPUProcAddress("glBlendFuncSeparate");
    glBlendFunci = (PFNGLBLENDFUNCIPROC)GetGPUProcAddress("glBlendFunci");
    glBlendColor = (PFNGLBLENDCOLORPROC)GetGPUProcAddress("glBlendColor");
    glPixelStorei = (PFNGLPIXELSTOREIPROC)GetGPUProcAddress("glPixelStorei");
    glPixelStoref = (PFNGLPIXELSTOREFPROC)GetGPUProcAddress("glPixelStoref");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetGPUProcAddress("glTexParameteri");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetGPUProcAddress("glGenerateMipmap");
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetGPUProcAddress("glTexSubImage2D");
    glPolygonMode = (PFNGLPOLYGONMODEPROC)GetGPUProcAddress("glPolygonMode");
    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)GetGPUProcAddress("glGetBufferParameteri64v");
    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)GetGPUProcAddress("glGetBufferParameteriv");
    glGetBufferParameterui64v = (PFNGLGETBUFFERPARAMETERI64VPROC)GetGPUProcAddress("glGetBufferParameterui64v");
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)GetGPUProcAddress("glGetBufferPointerv");
    glFenceSync = (PFNGLFENCESYNCPROC )GetGPUProcAddress("glFenceSync");
    glWaitSync = (PFNGLWAITSYNCPROC)GetGPUProcAddress("glWaitSync");
    glDeleteSync = (PFNGLDELETESYNCPROC)GetGPUProcAddress("glDeleteSync");
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC)GetGPUProcAddress("glDrawBuffers");
    glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)GetGPUProcAddress("glRenderbufferStorageMultisample");
    glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)GetGPUProcAddress("glBlitFramebuffer");
    glDepthFunc = (PFNGLDEPTHFUNCPROC)GetGPUProcAddress("glDepthFunc");
    glDepthMask = (PFNGLDEPTHMASKPROC)GetGPUProcAddress("glDepthMask");
    glPointSize = (PFNGLPOINTSIZEPROC)GetGPUProcAddress("glPointSize");
    glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)GetGPUProcAddress("glPointParameteriv");
    glPointParameteri = (PFNGLPOINTPARAMETERIPROC)GetGPUProcAddress("glPointParameteri");
    glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)GetGPUProcAddress("glPointParameterfv");
    glPointParameterf = (PFNGLPOINTPARAMETERFPROC)GetGPUProcAddress("glPointParameterf");
    glCullFace = (PFNGLCULLFACEPROC)GetGPUProcAddress("glCullFace");
    glLineWidth = (PFNGLLINEWIDTHPROC)GetGPUProcAddress("glLineWidth");
    glClearDepthf = (PFNGLCLEARDEPTHFPROC)GetGPUProcAddress("glClearDepthf");
    glClearDepth = (PFNGLCLEARDEPTHPROC)GetGPUProcAddress("glClearDepth");
}
}
