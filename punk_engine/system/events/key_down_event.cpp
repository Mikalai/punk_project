#include "key_down_event.h"

namespace System
{
    std::queue<KeyDownEvent*> KeyDownEvent::eventPool;

    KeyDownEvent::KeyDownEvent()
    {
        eventCode = EVENT_KEY_DOWN;
    }

    void KeyDownEvent::Release()
    {
        this->eventPool.push(this);
    }

    KeyDownEvent* KeyDownEvent::Raise()
    {
        if (eventPool.empty())
        {
            KeyDownEvent* event = new KeyDownEvent();
            return event;
        }
        else
        {
            KeyDownEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string KeyDownEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_DOWN; Key: %d; Repeat: %d; Scancode: %d \
IsExtended: %s; PrevState: %s; TransitionState: %s", eventCode, key,
							   repeat_count, scan_code, isExtended ? L"TRUE" : L"FALSE",
							   prevState ? L"TRUE" : L"FALSE",
							   transitionState ? L"TRUE" : L"FALSE");
	}
}
