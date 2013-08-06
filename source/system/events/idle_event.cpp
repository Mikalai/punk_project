#include "idle_event.h"

namespace System
{
    IdleEvent::IdleEvent()
    {
        eventCode = EVENT_IDLE;
    }

	string IdleEvent::ToString()
	{
		return string("Code: %d; Type: IDLE", eventCode);
	}
}
