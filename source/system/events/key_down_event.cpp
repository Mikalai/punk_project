#include "key_down_event.h"

namespace System
{
    KeyDownEvent::KeyDownEvent()
    {
        eventCode = EVENT_KEY_DOWN;
    }

	string KeyDownEvent::ToString()
	{
        return string("Code: {0}; Type: KEY_DOWN; Key: {1}; Repeat: {2}; Scancode: {3}; IsExtended: {4}; PrevState: {5}; TransitionState: {6}")
                .arg(eventCode).arg(key).arg(repeat_count).arg(scan_code).arg(isExtended ? L"TRUE" : L"FALSE").arg(prevState ? L"TRUE" : L"FALSE")
                .arg(transitionState ? L"TRUE" : L"FALSE");
	}
}
