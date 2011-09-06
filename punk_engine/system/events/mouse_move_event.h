#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include "event.h"

namespace System
{
    class LIB_SYSTEM MouseMoveEvent : public Event
    {
        static std::queue<MouseMoveEvent*> eventPool;
        MouseMoveEvent();
        MouseMoveEvent(const MouseMoveEvent&);
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
        static MouseMoveEvent* Raise();
    };
}

#endif // MOUSE_MOVE_EVENT_H
