#include "mouse_left_button_up.h"

namespace System
{
    std::queue<MouseLeftButtonUpEvent*> MouseLeftButtonUpEvent::eventPool;

    MouseLeftButtonUpEvent::MouseLeftButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_LBUTTON_UP;
    }

    void MouseLeftButtonUpEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseLeftButtonUpEvent* MouseLeftButtonUpEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseLeftButtonUpEvent* event = new MouseLeftButtonUpEvent();
            return event;
        }
        else
        {
            MouseLeftButtonUpEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseLeftButtonUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
