#ifndef SET_UNFOCUSED_EVENT_H
#define SET_UNFOCUSED_EVENT_H

#include "event.h"

namespace System
{
    class MODULE_SYSTEM SetUnFocusedEvent : public Event
    {
        static std::queue<SetUnFocusedEvent*> eventPool;
        SetUnFocusedEvent();
        SetUnFocusedEvent(const SetUnFocusedEvent&);
		SetUnFocusedEvent& operator = (const SetUnFocusedEvent&);
    public:
		virtual void Release();
		virtual string ToString();
        static SetUnFocusedEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
