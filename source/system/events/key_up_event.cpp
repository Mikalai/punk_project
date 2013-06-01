#include "key_up_event.h"

namespace System
{
    KeyUpEvent::KeyUpEvent()
    {
        eventCode = EVENT_KEY_UP;
    }

	string KeyUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_UP; Key: %d;", eventCode, key);
	}
}
