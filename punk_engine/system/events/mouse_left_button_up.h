#ifndef MOUSE_LEFT_BUTTON_UP_H
#define MOUSE_LEFT_BUTTON_UP_H

#include "event.h"

namespace System
{
    class MODULE_SYSTEM MouseLeftButtonUpEvent : public Event
    {
        static std::queue<MouseLeftButtonUpEvent*> eventPool;
        MouseLeftButtonUpEvent();
        MouseLeftButtonUpEvent(const MouseLeftButtonUpEvent&);
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
        static MouseLeftButtonUpEvent* Raise();
    };
}

#endif // MOUSE_LEFT_BUTTON_UP_H
