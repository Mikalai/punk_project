#include "key_wchar_event.h"

namespace System
{
    KeyWCharEvent::KeyWCharEvent()
    {
        eventCode = EVENT_KEY_WCHAR;
    }

	string KeyWCharEvent::ToString()
	{
        return string("Code: {0}; Type: KEY_WCHAR; Key: {1}; Repeat: {2}; Scancode: {3}; IsExtended: {4}; IsAltPressed: {5}; PrevState: {6}; TransitionState: {7}")
                .arg(eventCode).arg(key).arg(repeat_count).arg(scan_code).arg(isExtended ? L"TRUE" : L"FALSE").arg(isAltPressed ? L"TRUE" : L"FALSE")
                .arg(prevState ? L"TRUE" : L"FALSE").arg(transitionState ? L"TRUE" : L"FALSE");
	}
}
