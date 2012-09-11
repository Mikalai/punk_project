#include "key_wchar_event.h"

namespace System
{
    std::queue<KeyWCharEvent*> KeyWCharEvent::eventPool;

    KeyWCharEvent::KeyWCharEvent()
    {
        eventCode = EVENT_KEY_WCHAR;
    }

    void KeyWCharEvent::Release()
    {
        this->eventPool.push(this);
    }

    KeyWCharEvent* KeyWCharEvent::Raise()
    {
        if (eventPool.empty())
        {
            KeyWCharEvent* event = new KeyWCharEvent();
            return event;
        }
        else
        {
            KeyWCharEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string KeyWCharEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_WCHAR; Key: %d; Repeat: %d; Scancode: %d; IsExtended: %d; \
							   IsAltPressed: %s; PrevState: %s; TransitionState: %s",
							   eventCode, key, repeat_count, scan_code,
							   isExtended ? L"TRUE" : L"FALSE",
							   isAltPressed ? L"TRUE" : L"FALSE",
							   prevState ? L"TRUE" : L"FALSE",
							   transitionState ? L"TRUE" : L"FALSE");
	}
}
