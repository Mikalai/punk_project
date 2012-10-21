#ifndef KEY_MOUSE_LEAVE_EVENT_H
#define KEY_MOUSE_LEAVE_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE MouseLeaveEvent : public Event, Poolable<MouseLeaveEvent>
    {        
        MouseLeaveEvent(const MouseLeaveEvent&);
		MouseLeaveEvent& operator = (const MouseLeaveEvent&);
    public:
		MouseLeaveEvent();
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
