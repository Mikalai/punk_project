#include "event_update.h"
#include "../../system/string.h"

namespace Logic
{
    std::queue<EventUpdate*> EventUpdate::eventPool;

    EventUpdate::EventUpdate()
    {
        eventCode = EVENT_UPDATE;
    }

    void EventUpdate::Release()
    {
        this->eventPool.push(this);
    }

    EventUpdate* EventUpdate::Raise()
    {
        if (eventPool.empty())
        {
            EventUpdate* event = new EventUpdate();
            return event;
        }
        else
        {
            EventUpdate* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	System::string EventUpdate::ToString()
	{
		return System::string::Format(L"Code: %d; Type: LOGIC_UPDATE; Delta: %f;",
			eventCode, time_in_ms);
	}

}
