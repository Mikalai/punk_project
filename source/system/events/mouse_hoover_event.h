#ifndef KEY_MOUSE_HOOVER_EVENT_H
#define KEY_MOUSE_HOOVER_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE MouseHooverEvent : public Event, public Poolable<MouseHooverEvent>
    {        
        MouseHooverEvent(const MouseHooverEvent&);
    public:
		MouseHooverEvent();
        int x, y;
		int x_prev, y_prev;
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
