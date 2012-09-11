#include "mouse_right_button_up.h"

namespace System
{
    std::queue<MouseRightButtonUpEvent*> MouseRightButtonUpEvent::eventPool;

    MouseRightButtonUpEvent::MouseRightButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_UP;
    }

    void MouseRightButtonUpEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseRightButtonUpEvent* MouseRightButtonUpEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseRightButtonUpEvent* event = new MouseRightButtonUpEvent();
            return event;
        }
        else
        {
            MouseRightButtonUpEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseRightButtonUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_RBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
