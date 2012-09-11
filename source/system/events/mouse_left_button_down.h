#ifndef MOUSE_LEFT_BUTTON_DOWN_H
#define MOUSE_LEFT_BUTTON_DOWN_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE MouseLeftButtonDownEvent : public Event
    {
        static std::queue<MouseLeftButtonDownEvent*> eventPool;
        MouseLeftButtonDownEvent();
        MouseLeftButtonDownEvent(const MouseLeftButtonDownEvent&);
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
        static MouseLeftButtonDownEvent* Raise();
    };
}
#endif // MOUSE_LEFT_BUTTON_DOWN_H
