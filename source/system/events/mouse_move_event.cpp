#include "mouse_move_event.h"

namespace System
{
    std::queue<MouseMoveEvent*> MouseMoveEvent::eventPool;

    MouseMoveEvent* MouseMoveEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseMoveEvent* event = new MouseMoveEvent();
            return event;
        }
        else
        {
            MouseMoveEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

    void MouseMoveEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseMoveEvent::MouseMoveEvent()
    {
        eventCode = EVENT_MOUSE_MOVE;
    }

	string MouseMoveEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_MOVE; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
