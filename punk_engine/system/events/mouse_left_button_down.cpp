#include "mouse_left_button_down.h"

namespace System
{
    std::queue<MouseLeftButtonDownEvent*> MouseLeftButtonDownEvent::eventPool;

    MouseLeftButtonDownEvent::MouseLeftButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_LBUTTON_DOWN;
    }

    void MouseLeftButtonDownEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseLeftButtonDownEvent* MouseLeftButtonDownEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseLeftButtonDownEvent* event = new MouseLeftButtonDownEvent();
            return event;
        }
        else
        {
            MouseLeftButtonDownEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseLeftButtonDownEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
