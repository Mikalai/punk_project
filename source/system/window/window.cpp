#ifdef __gnu_linux__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/keysym.h>
typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPbuffer;
typedef XID GLXPixmap;
typedef XID GLXWindow;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXDrawable;
typedef XID GLXContextID;
#endif

#include <stdio.h>
#include <algorithm>

#include "../errors/module.h"
#include "window.h"
#include "../../math/helper.h"
#include "../event_manager.h"
#include "../logger.h"
#include "../input/module.h"
#include "../timer.h"

namespace System
{

#ifdef _WIN32
LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT WINAPI (*TWindowCallBack)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int GetX(HWND handle)
{
    RECT wrect;
    GetClientRect(handle, &wrect);
    return wrect.left;
}

int GetY(HWND handle)
{
    RECT wrect;
    GetClientRect(handle, &wrect);
    return wrect.top;
}

int GetWidth(HWND handle)
{
    RECT rect;
    GetClientRect(handle, &rect);
    return rect.right - rect.left;
}

int GetHeight(HWND handle)
{
    RECT rect;;
    GetClientRect(handle, &rect);
    return rect.bottom - rect.top;
}
#endif

struct Window::Impl
{
#ifdef _WIN32
    HWND m_hwindow;
    bool m_use_parent_window;
    TWindowCallBack m_prev_hwnd_func;
#elif defined __gnu_linux__
    Display* m_display;
    ::Window m_window;
    Screen* m_screen;
    Colormap m_color_map;
    bool m_buttons[256];
    WindowAdapter* m_adapter;
    bool m_exit_main_loop;
#endif

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
    void SetSize(int width, int height);
    void SetPosition(int x, int y);
    int Loop();
    void BreakMainLoop();
    void SetTitle(const string& text);
    const string GetTitle() const;
    void Quite();
    void DrawPixel(int x, int y);
    void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void DrawLine(int x1, int y1, int x2, int y2);
#ifdef _WIN32
    operator HWND ();
    LRESULT CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#elif defined __gnu_linux__
    int DecodeKey(KeySym keysym, int& charKey, bool press);
    void OnKeyPressRelease(XKeyEvent *event);
#endif
};

Window::Impl::Impl(WindowAdapter* adapter, const WindowDesc& desc)
#ifdef _WIN32
    : m_prev_hwnd_func(DefWindowProc)
    #endif
{
#ifdef _WIN32
    if (desc.m_use_parent_window)
    {
        m_use_parent_window = true;
        m_hwindow = desc.m_hwnd;
        m_prev_hwnd_func = (TWindowCallBack)GetWindowLong(m_hwindow, GWL_WNDPROC);
        SetWindowLongW(m_hwindow, GWL_WNDPROC, (LONG)WindowCallBack);
    }
    else
    {
        m_use_parent_window = false;
        WNDCLASS wc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = LoadCursor(0, IDC_ARROW);
        wc.hIcon = LoadIcon(0, IDI_APPLICATION);
        wc.hInstance = GetModuleHandle(0);
        wc.lpfnWndProc = WindowCallBack;
        wc.lpszClassName = TEXT("Punk Render");
        wc.lpszMenuName = 0;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        if (!RegisterClass(&wc))
            throw PunkInvalidArgumentException(L"Can't register window class");

        RECT rect;
        rect.left = desc.m_x;
        rect.right = desc.m_x + desc.m_width;
        rect.top = desc.m_y;
        rect.bottom = desc.m_y + desc.m_height;


        DWORD style = WS_OVERLAPPEDWINDOW;
        DWORD styleEx = 0;

        AdjustWindowRectEx(&rect, style, false, styleEx);

        m_hwindow = CreateWindowEx(styleEx, TEXT("Punk Render"), TEXT("Punk Engine"), style,
                                   0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0,
                                   GetModuleHandle(0), (void*)adapter);

        SetWindowLongPtr(m_hwindow, GWLP_USERDATA, (LONG)adapter);

        if (!m_hwindow)
            throw PunkInvalidArgumentException(L"Can't create window");

        GetClientRect(m_hwindow, &rect);
        ShowWindow(m_hwindow, SW_SHOW);
        UpdateWindow(m_hwindow);
    }
#elif defined __gnu_linux__
    m_exit_main_loop = false;
    m_adapter = adapter;
    m_display = XOpenDisplay(NULL);
    if (m_display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    auto m_screen = DefaultScreen(m_display);
    XSetWindowAttributes swa;
    memset(&swa, 0, sizeof(swa));
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap( m_display,
                                           RootWindow( m_display, m_screen),
                                           XDefaultVisual(m_display, m_screen), AllocNone );
    swa.border_pixel      = 0;
    swa.event_mask        = KeyPressMask    | ExposureMask
            | ButtonPressMask | StructureNotifyMask;
    swa.background_pixel = BlackPixel(m_display, m_screen);
    /*StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
            | EnterWindowMask
            | LeaveWindowMask
            | PointerMotionMask
            | PointerMotionHintMask
            | Button1MotionMask
            | Button2MotionMask
            | Button3MotionMask
            | Button4MotionMask
            | Button5MotionMask
            | ButtonMotionMask
            | KeymapStateMask
            | ExposureMask
            | VisibilityChangeMask
            | StructureNotifyMask
            | ResizeRedirectMask
            | SubstructureNotifyMask
            | SubstructureRedirectMask
            | FocusChangeMask
            | PropertyChangeMask
            | ColormapChangeMask
            | OwnerGrabButtonMask;*/

   // auto ww = XCreateSimpleWindow(m_display, RootWindow(m_display, m_screen), 100, 100, 600, 600, 0, BlackPixel(m_display, m_screen),
     //                  WhitePixel(m_display, m_screen));

 //   XMapWindow(m_display, ww);

    //XFlush(m_display);

    printf( "Creating window\n" );
    m_window = XCreateWindow( m_display, RootWindow(m_display, m_screen),
                              desc.m_x, desc.m_y, desc.m_width, desc.m_height, 0, 0, InputOutput, XDefaultVisual(m_display, m_screen), CWBackPixel|CWBorderPixel|CWColormap|CWEventMask, &swa );
//    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
//             | EnterWindowMask
//             | LeaveWindowMask
//             | PointerMotionMask
//             | PointerMotionHintMask
//             | Button1MotionMask
//             | Button2MotionMask
//             | Button3MotionMask
//             | Button4MotionMask
//             | Button5MotionMask
//             | ButtonMotionMask
//             | KeymapStateMask
//             | ExposureMask
//             | VisibilityChangeMask
//             | StructureNotifyMask
//             | ResizeRedirectMask
//             | SubstructureNotifyMask
//             | SubstructureRedirectMask
//             | FocusChangeMask
//             | PropertyChangeMask
//             | ColormapChangeMask
//             | OwnerGrabButtonMask);
    XMapWindow(m_display, m_window);
#endif
}

Window::Impl::~Impl()
{
#ifdef _WIN32
    SetWindowLong(m_hwindow, GWL_WNDPROC, (LONG)m_prev_hwnd_func);
    DestroyWindow(m_hwindow);
#elif defined __gnu_linux__
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
#endif
}

int Window::Impl::GetDesktopWidth() const
{
#ifdef _WIN32
    DEVMODE mode;
    memset(&mode, 0, sizeof(mode));
    mode.dmSize = sizeof(mode);

    if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
        return 480;
    return mode.dmPelsWidth;
#elif defined __gnu_linux__
    return WidthOfScreen(m_screen);
#endif
}

int Window::Impl::GetDesktopHeight() const
{
#ifdef _WIN32
    DEVMODE mode;
    memset(&mode, 0, sizeof(mode));
    mode.dmSize = sizeof(mode);

    if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
        return 640;
    return mode.dmPelsHeight;
#elif defined __gnu_linux__
    return HeightOfScreen(m_screen);
#endif
}

int Window::Impl::GetDesktopBitsPerPixel() const
{
#ifdef _WIN32
    DEVMODE mode;
    memset(&mode, 0, sizeof(mode));
    mode.dmSize = sizeof(mode);

    if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
        return 16;
    return mode.dmBitsPerPel;
#elif defined __gnu_linux__
    auto screen = XDefaultScreenOfDisplay(m_display);
    screen->root_visual->bits_per_rgb;
#endif
}

int Window::Impl::GetDesktopRefreshRate() const
{
#ifdef _WIN32
    DEVMODE mode;
    memset(&mode, 0, sizeof(mode));
    mode.dmSize = sizeof(mode);

    if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
        return 60;
    return mode.dmDisplayFrequency;
#elif defined __gnu_linux__
    auto screen = XDefaultScreenOfDisplay(m_display);
    screen;
#endif
}

int Window::Impl::GetWidth() const
{
#ifdef _WIN32
    RECT rect;
    GetClientRect(m_hwindow, &rect);
    return rect.right - rect.left;
#elif defined __gnu_linux__
    XWindowAttributes attr;
    XGetWindowAttributes(m_display, m_window, &attr);
    return attr.width;
#endif
}

int Window::Impl::GetHeight() const
{
#ifdef _WIN32
    RECT rect;;
    if (!GetClientRect(m_hwindow, &rect))
        throw PunkInvalidArgumentException(L"Can't get window height");
    //GetWindowRect(m_hwindow, &rect);
    return rect.bottom - rect.top;
#elif defined __gnu_linux__
    XWindowAttributes attr;
    XGetWindowAttributes(m_display, m_window, &attr);
    return attr.height;
#endif
}

int Window::Impl::GetX() const
{
#ifdef _WIN32
    RECT wrect;
    GetClientRect(m_hwindow, &wrect);
    return wrect.left;
#elif defined __gnu_linux__
    XWindowAttributes attr;
    XGetWindowAttributes(m_display, m_window, &attr);
    return attr.x;
#endif
}

int Window::Impl::GetY() const
{
#ifdef _WIN32
    RECT wrect;
    GetClientRect(m_hwindow, &wrect);
    return wrect.top;
#elif defined __gnu_linux__
    XWindowAttributes attr;
    XGetWindowAttributes(m_display, m_window, &attr);
    return attr.y;
#endif
}

void Window::Impl::SetSize(int width, int height)
{
#ifdef _WIN32
    RECT r;
    GetWindowRect(m_hwindow, &r);
    r.right = r.left + width;
    r.bottom = r.top + height;
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
    MoveWindow(m_hwindow, r.left, r.top, width, height, TRUE);
#elif defined __gnu_linux__
    XWindowChanges v;
    v.width = width;
    v.height = height;
    XConfigureWindow(m_display, m_window, CWWidth | CWHeight, &v);
#endif
}

void Window::Impl::SetPosition(int x, int y)
{
#ifdef _WIN32
    RECT r;
    GetWindowRect(m_hwindow, &r);
    MoveWindow(m_hwindow, x, y, r.right - r.left, r.bottom - r.top, TRUE);
#elif defined __gnu_linux__
    XWindowChanges v;
    v.x = x;
    v.y = y;
    XConfigureWindow(m_display, m_window, CWX | CWY, &v);
#endif
}

#ifdef __gnu_linux__
int Window::Impl::DecodeKey(KeySym keysym, int& charKey, bool press)
{
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
    if (XLookupString(event,buffer,1, &keysym,NULL) == 1)
    {
        key = DecodeKey(keysym, charKey, press);
        if (press)
        {
            KeyDownEvent* e = new KeyDownEvent;
            e->key = key;
            m_adapter->WndOnKeyDownEvent(e);
        }
        else
        {
            KeyUpEvent* e = new KeyUpEvent;
            e->key = key;
            m_adapter->WndOnKeyUpEvent(e);
        }

        if (charKey != 0 && press)
        {
            KeyCharEvent* e = new KeyCharEvent;
            e->key = key;
            m_adapter->WndOnCharEvent(e);
        }
    }
}
#endif

int Window::Impl::Loop()
{
    Timer timer;
    timer.Reset();

#ifdef _WIN32
    if (m_use_parent_window)
        return 0;

    MSG msg;
    WindowAdapter* adapter = reinterpret_cast<WindowAdapter*>(GetWindowLongPtr(m_hwindow, GWLP_USERDATA));
    if (!adapter)
        throw PunkInvalidArgumentException(L"Can't get window adapter interface");

    while (1)
    {
        while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
        {
            if (GetMessage(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                return 0;
            }
        }

        IdleEvent* e = new IdleEvent;
        e->elapsed_time_s = timer.GetElapsedSeconds();
        timer.Reset();
        adapter->WndOnIdleEvent(e);
    }
#elif defined __gnu_linux__

    static int x_prev = 0;
    static int y_prev = 0;
    static int x = 0;
    static int y = 0;

    XEvent event;
    while (1)
    {
        if (m_exit_main_loop)
            break;
        do
        {
            //XNextEvent(display, &event);
            if (!XCheckWindowEvent(m_display, m_window, -1l, &event))
                break;

            switch (event.type)
            {
            case CreateNotify:
            {
                m_adapter->WndOnCreateEvent();
                break;
            }
            case DestroyNotify:
            {
                m_adapter->WndOnDestroyEvent();
                break;
            }
            case ConfigureNotify:
            {
                WindowResizeEvent* e = new WindowResizeEvent();                
                e->width = event.xconfigure.width;
                e->height = event.xconfigure.height;
                m_adapter->WndOnResizeEvent(e);
                break;
            }
            case Expose:
            {
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
                e->x = event.xmotion.x;
                e->y = event.xmotion.y;
                /*event->controlKey = (bool)(wParam & MK_CONTROL);
event->leftButton = (bool)(wParam & MK_LBUTTON);
event->middleButton = (bool)(wParam & MK_MBUTTON);
event->rightButton = (bool)(wParam & MK_RBUTTON);
event->shiftButton = (bool)(wParam & MK_SHIFT);
event->xbutton1 = (bool)(wParam & MK_XBUTTON1);
event->xbutton2 = (bool)(wParam & MK_XBUTTON2);*/
                m_adapter->WndOnMouseMoveEvent(e);
                break;
            }
            case ButtonPress:
            case ButtonRelease:
            {
                bool press = event.type == ButtonPress;
                switch (event.xbutton.button)
                {
                case 1: //LEFT
                {
                    if (press)
                    {
                        MouseLeftButtonDownEvent* e = new MouseLeftButtonDownEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, true);
                        m_adapter->WndOnMouseLeftButtonDownEvent(e);
                    }
                    else
                    {
                        MouseLeftButtonUpEvent* e = new MouseLeftButtonUpEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, false);
                        m_adapter->WndOnMouseLeftButtonUpEvent(e);
                    }
                }
                    break;
                case 2: //Middle
                    if (press)
                    {
                        MouseMiddleButtonDownEvent* e = new MouseMiddleButtonDownEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, true);
                        m_adapter->WndOnMouseMiddleButtonDownEvent(e);
                    }
                    else
                    {
                        MouseMiddleButtonUpEvent* e = new MouseMiddleButtonUpEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, false);
                        m_adapter->WndOnMouseMiddleButtonUpEvent(e);
                    }
                    break;
                case 3: //Right
                    if (press)
                    {
                        MouseRightButtonDownEvent* e = new MouseRightButtonDownEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, true);
                        m_adapter->WndOnMouseRightButtonDownEvent(e);
                    }
                    else
                    {
                        MouseRightButtonUpEvent* e = new MouseRightButtonUpEvent;
                        e->x = event.xbutton.x;
                        e->y = GetHeight() - event.xbutton.y;
                        e->x_prev = x_prev;
                        e->y_prev = y_prev;
                        x_prev = e->x;
                        y_prev = e->y;
                        //event->controlKey = (wParam & MK_CONTROL) != 0;
                        //event->leftButton = (wParam & MK_LBUTTON) != 0;
                        //event->middleButton = (wParam & MK_MBUTTON) != 0;
                        //event->rightButton = (wParam & MK_RBUTTON) != 0;
                        //event->shiftButton = (wParam & MK_SHIFT) != 0;
                        //event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
                        //event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
                        Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, false);
                        m_adapter->WndOnMouseRightButtonUpEvent(e);
                    }
                    break;
                case 4: //Whell +
                {
                    MouseWheelEvent* e = new MouseWheelEvent;
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
                    m_adapter->WndOnMouseWheelEvent(e);
                }
                    break;
                case 5: //wheel -
                {

                    MouseWheelEvent* e = new MouseWheelEvent;
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
                    m_adapter->WndOnMouseWheelEvent(e);;
                    break;
                }
                }
            }
                break;
            }
        }
        while (XPending(m_display)); /* loop to compress events */

        IdleEvent* e = new IdleEvent;
        e->elapsed_time_s = timer.GetElapsedSeconds();
        timer.Reset();
        if (m_adapter)
            m_adapter->WndOnIdleEvent(e);
    }
#endif
    return 0;
}

void Window::Impl::BreakMainLoop()
{
#ifdef _WIN32
    PostQuitMessage(0);
#elif defined __gnu_linux__
    m_exit_main_loop = true;
#endif
}

void Window::Impl::SetTitle(const string& text)
{
#ifdef _WIN32
    SetWindowText(m_hwindow, text.ToStdWString().c_str());
#elif defined __gnu_linux__
#endif
}

const string Window::Impl::GetTitle() const
{
#ifdef _WIN32
    wchar_t buf[256];
    GetWindowText(m_hwindow, buf, 256);
    return string(buf);
#elif defined __gnu_linux__
#endif
}

void Window::Impl::Quite()
{
#ifdef _WIN32
    SendMessage(m_hwindow, WM_DESTROY, 0, 0);
#elif defined __gnu_linux__
#endif
}

void Window::Impl::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char rr = Math::Max((int)r - int(255 - a), 0);
    unsigned char gg = Math::Max((int)g - int(255 - a), 0);
    unsigned char bb = Math::Max((int)b - int(255 - a), 0);
#ifdef _WIN32
    SetPixel(GetDC(m_hwindow), x, y, RGB( rr, gg, bb));
#elif defined __gnu_linux__
#endif
}

void Window::Impl::DrawLine(int x1, int y1, int x2, int y2)
{
#ifdef _WIN32
    POINT p;
    MoveToEx(GetDC(m_hwindow), x1, y1, &p);
    LineTo(GetDC(m_hwindow), x2, y2);
    MoveToEx(GetDC(m_hwindow), p.x, p.y, 0);
#elif defined __gnu_linux__
#endif
}

#ifdef _WIN32
Window::Impl::operator HWND ()
{
    return m_hwindow;
}

LRESULT Window::Impl::CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (m_prev_hwnd_func)
        return m_prev_hwnd_func(hwnd, msg, wParam, lParam);
    else
        return DefWindowProc(hwnd, msg, wParam, lParam);

}
#endif

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

#ifdef _WIN32
LRESULT Window::CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return impl->CustomDefWindowProc(hwnd, msg, wParam, lParam);
}
#endif

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

#ifdef _WIN32
Window::operator HWND()
{
    return *impl;
}

#elif defined __gnu_linux__
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
}

::Window Window::GetWindow()
{
    return impl->m_window;
}

#endif


#ifdef _WIN32

LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WindowAdapter* adapter = reinterpret_cast<WindowAdapter*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    /*if (!adapter)
throw PunkInvalidArgumentException(L"Can't get window adapter interface");*/

    static int x_prev = 0;
    static int y_prev = 0;
    static int x = 0;
    static int y = 0;

    switch (msg)
    {
    case WM_MBUTTONUP:
    {
        MouseMiddleButtonUpEvent* event = new MouseMiddleButtonUpEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, false);
        adapter->WndOnMouseMiddleButtonUpEvent(event);
    }
        break;
    case WM_MBUTTONDOWN:
    {
        MouseMiddleButtonDownEvent* event = new MouseMiddleButtonDownEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, true);
        adapter->WndOnMouseMiddleButtonDownEvent(event);
    }
        break;
    case WM_RBUTTONUP:
    {
        MouseRightButtonUpEvent* event = new MouseRightButtonUpEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, false);
        adapter->WndOnMouseRightButtonUpEvent(event);
    }
        break;
    case WM_RBUTTONDOWN:
    {
        MouseRightButtonDownEvent* event = new MouseRightButtonDownEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, true);
        adapter->WndOnMouseRightButtonDownEvent(event);
    }
        break;
    case WM_LBUTTONUP:
    {
        MouseLeftButtonUpEvent* event = new MouseLeftButtonUpEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, false);
        adapter->WndOnMouseLeftButtonUpEvent(event);
    }
        break;
    case WM_LBUTTONDOWN:
    {
        MouseLeftButtonDownEvent* event = new MouseLeftButtonDownEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, true);
        adapter->WndOnMouseLeftButtonDownEvent(event);
    }
        break;
    case WM_MOUSEHOVER:
    {
        MouseHooverEvent* event = new MouseHooverEvent;
        event->x = LOWORD(lParam);
        event->y = GetHeight(hwnd) - HIWORD(lParam);
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        adapter->WndOnMouseHooverEvent(event);
    }
        break;
    case WM_MOUSEMOVE:
    {
        MouseMoveEvent* event = new MouseMoveEvent;

        x_prev = x;
        y_prev = y;
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        event->x = x;
        event->y = GetHeight(hwnd) - y;
        event->x_prev = x_prev;
        event->y_prev = GetHeight(hwnd) - y_prev;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;

        if (Mouse::Instance()->IsLocked())
        {
            RECT r, r2;
            GetWindowRect(hwnd, &r);
            GetClientRect(hwnd, &r2);
            int c_x = (r.left + r.right) / 2;
            int c_y = (r.top + r.bottom) / 2;
            POINT p = {c_x, c_y};
            ClientToScreen(hwnd, &p);
            if (x != x_prev || y != y_prev)
            {
                x = x_prev = c_x;
                y = y_prev = c_y;
                SetCursorPos(p.x, p.y);
            }
        }

        TRACKMOUSEEVENT te;
        memset(&te, 0, sizeof(te));
        te.cbSize = sizeof(te);
        te.dwFlags = TME_HOVER;
        te.dwHoverTime = 400;
        te.hwndTrack = hwnd;
        TrackMouseEvent(&te);
        adapter->WndOnMouseMoveEvent(event);
    }
        break;
    case WM_MOUSEWHEEL:
    {
        POINT p = {LOWORD(lParam), HIWORD(lParam)};
        ScreenToClient(hwnd, &p);
        MouseWheelEvent* event = new MouseWheelEvent;
        event->x = p.x;
        event->y = GetHeight(hwnd) - p.y;
        event->x_prev = x_prev;
        event->y_prev = y_prev;
        x_prev = event->x;
        y_prev = event->y;
        event->delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
        event->controlKey = (wParam & MK_CONTROL) != 0;
        event->leftButton = (wParam & MK_LBUTTON) != 0;
        event->middleButton = (wParam & MK_MBUTTON) != 0;
        event->rightButton = (wParam & MK_RBUTTON) != 0;
        event->shiftButton = (wParam & MK_SHIFT) != 0;
        event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
        event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
        adapter->WndOnMouseWheelEvent(event);
    }
        break;
    case WM_CHAR:
    {
        KeyCharEvent* event = new KeyCharEvent;
        event->key = (int)wParam;
        event->repeat_count = (lParam & 0xFFFF) != 0;
        event->scan_code = (lParam & 0xFF0000) != 0;
        event->isExtended = (lParam & 0x1000000) != 0;
        event->isAltPressed = (lParam & 0x20000000) != 0;
        event->prevState = (lParam & 0x40000000) != 0;
        event->transitionState = (lParam & 0x80000000) != 0;
        adapter->WndOnCharEvent(event);
    }
        break;
    case WM_UNICHAR:
    {
        KeyWCharEvent* event = new KeyWCharEvent;
        event->key = (int)wParam;
        event->repeat_count = (lParam & 0xFFFF) != 0;
        event->scan_code = (lParam & 0xFF0000) != 0;
        event->isExtended = (lParam & 0x1000000) != 0;
        event->isAltPressed = (lParam & 0x20000000) != 0;
        event->prevState = (lParam & 0x40000000) != 0;
        event->transitionState = (lParam & 0x80000000) != 0;
        adapter->WndOnWideCharEvent(event);
    }
        break;
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    {
        KeyDownEvent* event = new KeyDownEvent;
        event->key = (int)wParam;
        event->repeat_count = (lParam & 0xFFFF) != 0;
        event->scan_code = (lParam & 0xFF0000) != 0;
        event->isExtended = (lParam & 0x1000000) != 0;
        event->prevState = (lParam & 0x40000000) != 0;
        event->transitionState = (lParam & 0x80000000) != 0;
        Keyboard::Instance()->SetKeyState(wParam, true);
        adapter->WndOnKeyDownEvent(event);
        break;
    }
    case WM_SYSKEYUP:
    case WM_KEYUP:
    {
        KeyUpEvent* event = new KeyUpEvent;
        event->key = (int)wParam;
        Keyboard::Instance()->SetKeyState(wParam, false);
        adapter->WndOnKeyUpEvent(event);
        break;
    }
    case WM_SIZE:
    {
        WindowResizeEvent* event = new WindowResizeEvent;
        event->minimized = (wParam & SIZE_MINIMIZED) != 0;
        event->restored = (wParam & SIZE_RESTORED) != 0;
        event->width = LOWORD(lParam);
        event->height = HIWORD(lParam);
        adapter->WndOnResizeEvent(event);

        /*		RECT r;
GetWindowRect(window->m_hwindow, &r);
x_prev = (r.left + r.right)/2;
y_prev = (r.top + r.bottom)/2;
SetCursorPos((r.left+r.right)/2, (r.top+r.bottom)/2);*/
    }
        break;
    case WM_CREATE:
    {
        //MessageBoxA(0, "sdfg", "SDFG", MB_OK);
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        RECT r;
        GetWindowRect(hwnd, &r);
        x_prev = (r.left + r.right)/2;
        y_prev = (r.top + r.bottom)/2;
        SetCursorPos((r.left+r.right)/2, (r.top+r.bottom)/2);
        auto a = reinterpret_cast<WindowAdapter*>(cs->lpCreateParams);
        a->WndOnCreateEvent();
    }
        break;
    case WM_DESTROY:
        adapter->WndOnDestroyEvent();
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
#endif	//	_WIN32

}
