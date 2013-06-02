#ifndef MOUSE_LEFT_BUTTON_DOWN_H
#define MOUSE_LEFT_BUTTON_DOWN_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API MouseLeftButtonDownEvent : public Event, public Poolable<MouseLeftButtonDownEvent>
    {        
        MouseLeftButtonDownEvent(const MouseLeftButtonDownEvent&);
    public:
		MouseLeftButtonDownEvent();

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
#endif // MOUSE_LEFT_BUTTON_DOWN_H
