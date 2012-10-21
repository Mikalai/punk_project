#include "focused.h"

namespace System
{
 //   std::queue<SetFocusedEvent*> SetFocusedEvent::eventPool;

    SetFocusedEvent::SetFocusedEvent()
    {
		eventCode = EVENT_SET_FOCUSED;
    }

  /*  void SetFocusedEvent::Release()
    {
        this->eventPool.push(this);
    }

    SetFocusedEvent* SetFocusedEvent::Raise()
    {
        if (eventPool.empty())
        {
            SetFocusedEvent* event = new SetFocusedEvent();
            return event;
        }
        else
        {
            SetFocusedEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }
*/
	string SetFocusedEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: FOCUSED", eventCode);
	}
}
