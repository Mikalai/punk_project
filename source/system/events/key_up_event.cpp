#include "key_up_event.h"

namespace System
{
    KeyUpEvent::KeyUpEvent()
    {
        eventCode = EVENT_KEY_UP;
    }

	string KeyUpEvent::ToString()
	{
        return string("Code: {0}; Type: KEY_UP; Key: {1};").arg(eventCode).arg(key);
	}
}
