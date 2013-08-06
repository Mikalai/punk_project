#include "unfocused.h"

namespace GUI
{
    SetUnFocusedEvent::SetUnFocusedEvent()
    {
		eventCode = System::EVENT_SET_UNFOCUSED;
    }

	System::string SetUnFocusedEvent::ToString()
	{
        return System::string("Code: {0}; Type: UNFOCUSED").arg(eventCode);
	}
}
