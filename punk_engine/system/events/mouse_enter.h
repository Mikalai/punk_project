#ifndef KEY_MOUSE_ENTER_EVENT_H
#define KEY_MOUSE_ENTER_EVENT_H

#include "event.h"

namespace System
{
    class LIB_SYSTEM MouseEnterEvent : public Event
    {
        static std::queue<MouseEnterEvent*> eventPool;
        MouseEnterEvent();
        MouseEnterEvent(const MouseEnterEvent&);
    public:
		virtual void Release();
		virtual string ToString();
        static MouseEnterEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
