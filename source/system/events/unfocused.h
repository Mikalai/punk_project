#ifndef SET_UNFOCUSED_EVENT_H
#define SET_UNFOCUSED_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE SetUnFocusedEvent : public Event, public Poolable<SetUnFocusedEvent>
    {        
        SetUnFocusedEvent(const SetUnFocusedEvent&);
		SetUnFocusedEvent& operator = (const SetUnFocusedEvent&);
    public:
		SetUnFocusedEvent();
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
