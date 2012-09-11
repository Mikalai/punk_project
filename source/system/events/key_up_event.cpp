#include "key_up_event.h"

namespace System
{
    std::queue<KeyUpEvent*> KeyUpEvent::eventPool;

    KeyUpEvent::KeyUpEvent()
    {
        eventCode = EVENT_KEY_UP;
    }

    void KeyUpEvent::Release()
    {
        this->eventPool.push(this);
    }

    KeyUpEvent* KeyUpEvent::Raise()
    {
        if (eventPool.empty())
        {
            KeyUpEvent* event = new KeyUpEvent();
            return event;
        }
        else
        {
            KeyUpEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string KeyUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: KEY_UP; Key: %d;", eventCode, key);
	}
}
