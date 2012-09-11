#ifndef KEY_MOUSE_HOOVER_EVENT_H
#define KEY_MOUSE_HOOVER_EVENT_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE MouseHooverEvent : public Event
    {
        static std::queue<MouseHooverEvent*> eventPool;
        MouseHooverEvent();
        MouseHooverEvent(const MouseHooverEvent&);
    public:
        int x, y;
		int x_prev, y_prev;

		virtual void Release();
		virtual string ToString();
        static MouseHooverEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
