#include "key_char_event.h"

namespace System
{
    std::queue<KeyCharEvent*> KeyCharEvent::eventPool;

    KeyCharEvent::KeyCharEvent()
    {
        eventCode = EVENT_KEY_CHAR;
    }

    void KeyCharEvent::Release()
    {
        this->eventPool.push(this);
    }

    KeyCharEvent* KeyCharEvent::Raise()
    {
        if (eventPool.empty())
        {
            KeyCharEvent* event = new KeyCharEvent();
            return event;
        }
        else
        {
            KeyCharEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string KeyCharEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_CHAR", eventCode);
	}
}
