#ifndef SET_FOCUSED_EVENT_H
#define SET_FOCUSED_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE SetFocusedEvent : public Event
    {
        static std::queue<SetFocusedEvent*> eventPool;
        SetFocusedEvent();
        SetFocusedEvent(const SetFocusedEvent&);
		SetFocusedEvent& operator = (const SetFocusedEvent&);
    public:
		virtual void Release();
		virtual string ToString();
        static SetFocusedEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
