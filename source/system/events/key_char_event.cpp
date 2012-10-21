#include "key_char_event.h"

namespace System
{

    KeyCharEvent::KeyCharEvent()
    {
        eventCode = EVENT_KEY_CHAR;
    }

	string KeyCharEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_CHAR", eventCode);
	}
}
