/*
        File: window_linux.h
	Author: Abramau Mikalaj
	Description: Wrapper around os api
*/

#ifndef _H_LINUX_WINDOW
#define _H_LINUX_WINDOW

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#include <map>

#include "types_linux.h"

struct __GLXcontextRec;

namespace System
{
    class Window
    {
    public:
        Window();
        ~Window();
        void SubscribeHandler(unsigned message, Handler handler);
        void UnsubscribeHandler(unsigned message, Handler handler);
        int Loop();
        Display* GetDisplay();
        ::Window GetWindow();
        __GLXcontextRec* GetOpenGLContext();
        Colormap* GetColorMap();
    private:
        std::multimap<unsigned, Handler> m_handlers;
        Display* display;
        ::Window window;
        __GLXcontextRec* ctx;
        Colormap colorMap;
        bool buttons[256];
    };
}

#endif	//_H_LINUX_WINDOW
