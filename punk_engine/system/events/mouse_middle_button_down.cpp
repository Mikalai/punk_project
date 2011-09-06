#include "mouse_middle_button_down.h"

namespace System
{
    std::queue<MouseMiddleButtonDownEvent*> MouseMiddleButtonDownEvent::eventPool;

    MouseMiddleButtonDownEvent::MouseMiddleButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_DOWN;
    }

    void MouseMiddleButtonDownEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseMiddleButtonDownEvent* MouseMiddleButtonDownEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseMiddleButtonDownEvent* event = new MouseMiddleButtonDownEvent();
            return event;
        }
        else
        {
            MouseMiddleButtonDownEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseMiddleButtonDownEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_MBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
