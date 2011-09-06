#include "idle_event.h"

namespace System
{
    std::queue<IdleEvent*> IdleEvent::eventPool;

    IdleEvent::IdleEvent()
    {
        eventCode = EVENT_IDLE;
    }

    void IdleEvent::Release()
    {
        this->eventPool.push(this);
    }

    IdleEvent* IdleEvent::Raise()
    {
        if (eventPool.empty())
        {
            IdleEvent* event = new IdleEvent();
            return event;
        }
        else
        {
            IdleEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string IdleEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: IDLE", eventCode);
	}
}
