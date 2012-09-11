#ifndef _H_PUNK_WINDOW_RESIZE
#define _H_PUNK_WINDOW_RESIZE

#include "event.h"

namespace System
{
    class PUNK_ENGINE WindowResizeEvent : public Event
    {
        static std::queue<WindowResizeEvent*> eventPool;
        WindowResizeEvent();
        WindowResizeEvent(const WindowResizeEvent&);
    public:
        bool minimized;
		bool restored;
        int width, height;

        virtual void Release();
		virtual string ToString();
        static WindowResizeEvent* Raise();
    };
}

#endif