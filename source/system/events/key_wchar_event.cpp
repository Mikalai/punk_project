#include "key_wchar_event.h"

namespace System
{
    KeyWCharEvent::KeyWCharEvent()
    {
        eventCode = EVENT_KEY_WCHAR;
    }

	string KeyWCharEvent::ToString()
	{
		return string("Code: %d; Type: KEY_WCHAR; Key: %d; Repeat: %d; Scancode: %d; IsExtended: %d; \
							   IsAltPressed: %s; PrevState: %s; TransitionState: %s",
							   eventCode, key, repeat_count, scan_code,
							   isExtended ? L"TRUE" : L"FALSE",
							   isAltPressed ? L"TRUE" : L"FALSE",
							   prevState ? L"TRUE" : L"FALSE",
							   transitionState ? L"TRUE" : L"FALSE");
	}
}
