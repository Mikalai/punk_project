#ifndef MOUSE_RIGHT_BUTTON_DOWN_H
#define MOUSE_RIGHT_BUTTON_DOWN_H

#include "event.h"

namespace System
{
    class LIB_SYSTEM MouseRightButtonDownEvent : public Event
    {
        static std::queue<MouseRightButtonDownEvent*> eventPool;
        MouseRightButtonDownEvent();
        MouseRightButtonDownEvent(const MouseRightButtonDownEvent&);
    public:        
        int x, y;
		int x_prev, y_prev;
        bool controlKey : 1;
        bool leftButton : 1;
        bool middleButton : 1;
        bool rightButton  : 1;
        bool shiftButton  : 1;
        bool xbutton1 : 1;
        bool xbutton2 : 1;

        virtual void Release();
		virtual string ToString();
        static MouseRightButtonDownEvent* Raise();
    };
}

#endif // MOUSE_RIGHT_BUTTON_DOWN_H
