#ifndef MOUSE_RIGHT_BUTTON_UP_H
#define MOUSE_RIGHT_BUTTON_UP_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API MouseRightButtonUpEvent : public Event, public Poolable<MouseRightButtonUpEvent>
    {        
        MouseRightButtonUpEvent(const MouseRightButtonUpEvent&);
    public:        
		MouseRightButtonUpEvent();
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

#endif // MOUSE_RIGHT_BUTTON_UP_H
