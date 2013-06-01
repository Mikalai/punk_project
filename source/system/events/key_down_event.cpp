#include "key_down_event.h"

namespace System
{
    KeyDownEvent::KeyDownEvent()
    {
        eventCode = EVENT_KEY_DOWN;
    }

	string KeyDownEvent::ToString()
	{
		return string("Code: %d; Type: KEY_DOWN; Key: %d; Repeat: %d; Scancode: %d \
IsExtended: %s; PrevState: %s; TransitionState: %s", eventCode, key,
							   repeat_count, scan_code, isExtended ? L"TRUE" : L"FALSE",
							   prevState ? L"TRUE" : L"FALSE",
							   transitionState ? L"TRUE" : L"FALSE");
	}
}
