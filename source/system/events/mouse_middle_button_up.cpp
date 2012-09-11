#include "mouse_middle_button_up.h"

namespace System
{
    std::queue<MouseMiddleButtonUpEvent*> MouseMiddleButtonUpEvent::eventPool;

    MouseMiddleButtonUpEvent::MouseMiddleButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_UP;
    }

    void MouseMiddleButtonUpEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseMiddleButtonUpEvent* MouseMiddleButtonUpEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseMiddleButtonUpEvent* event = new MouseMiddleButtonUpEvent();
            return event;
        }
        else
        {
            MouseMiddleButtonUpEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseMiddleButtonUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_MBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
