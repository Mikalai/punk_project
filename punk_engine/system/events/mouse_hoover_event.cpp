#include "mouse_hoover_event.h"

namespace System
{
    std::queue<MouseHooverEvent*> MouseHooverEvent::eventPool;

    MouseHooverEvent::MouseHooverEvent()
    {
		eventCode = EVENT_MOUSE_HOOVER;
    }

    void MouseHooverEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseHooverEvent* MouseHooverEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseHooverEvent* event = new MouseHooverEvent();
            return event;
        }
        else
        {
            MouseHooverEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseHooverEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_HOOVER; x: %d; y: %d; x_prev: %d; y_prev: %d;",
			eventCode, x, y, x_prev, y_prev);
	}
}
