#include "mouse_leave.h"

namespace System
{
    std::queue<MouseLeaveEvent*> MouseLeaveEvent::eventPool;

    MouseLeaveEvent::MouseLeaveEvent()
    {
		eventCode = EVENT_MOUSE_LEAVE;
    }

    void MouseLeaveEvent::Release()
    {
        this->eventPool.push(this);
    }

    MouseLeaveEvent* MouseLeaveEvent::Raise()
    {
        if (eventPool.empty())
        {
            MouseLeaveEvent* event = new MouseLeaveEvent();
            return event;
        }
        else
        {
            MouseLeaveEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string MouseLeaveEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LEAVE;");
	}
}
