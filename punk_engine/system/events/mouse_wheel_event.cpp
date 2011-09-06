#include "mouse_wheel_event.h"

namespace System
{

    std::queue<MouseWheelEvent*> MouseWheelEvent::eventPool;

    MouseWheelEvent::MouseWheelEvent()
    {
        eventCode = EVENT_MOUSE_WHEEL;
    }

    void MouseWheelEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseWheelEvent* MouseWheelEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseWheelEvent* event = new MouseWheelEvent();
            return event;
        }
        else
        {
            MouseWheelEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseWheelEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_WHEEL; delta: %d; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, delta, x, y, x_prev, y_prev);
	}

}
