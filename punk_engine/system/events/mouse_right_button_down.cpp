#include "mouse_right_button_down.h"

namespace System
{
    std::queue<MouseRightButtonDownEvent*> MouseRightButtonDownEvent::eventPool;

    MouseRightButtonDownEvent::MouseRightButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_DOWN;
    }

    void MouseRightButtonDownEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseRightButtonDownEvent* MouseRightButtonDownEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseRightButtonDownEvent* event = new MouseRightButtonDownEvent();
            return event;
        }
        else
        {
            MouseRightButtonDownEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseRightButtonDownEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_RBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
