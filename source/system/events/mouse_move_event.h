#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE MouseMoveEvent : public Event, public Poolable<MouseMoveEvent>
    {        
        MouseMoveEvent(const MouseMoveEvent&);
    public:
		MouseMoveEvent();
        int x, y;
		int x_prev, y_prev;
        bool controlKey : 1;
        bool leftButton : 1;
        bool middleButton : 1;
        bool rightButton  : 1;
        bool shiftButton  : 1;
        bool xbutton1 : 1;
        bool xbutton2 : 1;

		virtual string ToString();
    };
}

#endif // MOUSE_MOVE_EVENT_H
