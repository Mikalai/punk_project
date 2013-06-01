#include "focused.h"

namespace GUI
{
 //   std::queue<SetFocusedEvent*> SetFocusedEvent::eventPool;

    SetFocusedEvent::SetFocusedEvent()
    {
		eventCode = System::EVENT_SET_FOCUSED;
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
	System::string SetFocusedEvent::ToString()
	{
		return System::string::Format(L"Code: %d; Type: FOCUSED", eventCode);
	}
}
