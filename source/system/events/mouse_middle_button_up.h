#ifndef MOUSE_MIDDLE_BUTTON_UP_H
#define MOUSE_MIDDLE_BUTTON_UP_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API MouseMiddleButtonUpEvent : public Event, public Poolable<MouseMiddleButtonUpEvent>
    {             
        MouseMiddleButtonUpEvent(const MouseMiddleButtonUpEvent&);
    public:  
		MouseMiddleButtonUpEvent();
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
#endif // MOUSE_MIDDLE_BUTTON_UP_H
