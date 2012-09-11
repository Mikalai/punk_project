#include "unfocused.h"

namespace System
{
    std::queue<SetUnFocusedEvent*> SetUnFocusedEvent::eventPool;

    SetUnFocusedEvent::SetUnFocusedEvent()
    {
		eventCode = EVENT_SET_UNFOCUSED;
    }

    void SetUnFocusedEvent::Release()
    {
        this->eventPool.push(this);
    }

    SetUnFocusedEvent* SetUnFocusedEvent::Raise()
    {
        if (eventPool.empty())
        {
            SetUnFocusedEvent* event = new SetUnFocusedEvent();
            return event;
        }
        else
        {
            SetUnFocusedEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	
	string SetUnFocusedEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: UNFOCUSED", eventCode);
	}
}
