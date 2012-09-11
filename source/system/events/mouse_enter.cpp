#include "mouse_enter.h"

namespace System
{
    std::queue<MouseEnterEvent*> MouseEnterEvent::eventPool;

    MouseEnterEvent::MouseEnterEvent()
    {
		eventCode = EVENT_MOUSE_ENTER;
    }

    void MouseEnterEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseEnterEvent* MouseEnterEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseEnterEvent* event = new MouseEnterEvent();
            return event;
        }
        else
        {
            MouseEnterEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseEnterEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_ENTER",
			eventCode);
	}
}
