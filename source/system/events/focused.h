#ifndef SET_FOCUSED_EVENT_H
#define SET_FOCUSED_EVENT_H

#include "event.h"
#include "../poolable.h"

namespace System
{
	class PUNK_ENGINE SetFocusedEvent : public Event, public Poolable<SetFocusedEvent>
    {        
        SetFocusedEvent(const SetFocusedEvent&);
		SetFocusedEvent& operator = (const SetFocusedEvent&);
    public:
		SetFocusedEvent();
		virtual string ToString();
        //static SetFocusedEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
