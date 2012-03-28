#ifndef KEY_MOUSE_LEAVE_EVENT_H
#define KEY_MOUSE_LEAVE_EVENT_H

#include "event.h"

namespace System
{
    class MODULE_SYSTEM MouseLeaveEvent : public Event
    {
        static std::queue<MouseLeaveEvent*> eventPool;
        MouseLeaveEvent();
        MouseLeaveEvent(const MouseLeaveEvent&);
		MouseLeaveEvent& operator = (const MouseLeaveEvent&);
    public:
		virtual void Release();
		virtual string ToString();

        static MouseLeaveEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
