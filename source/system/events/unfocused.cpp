#include "unfocused.h"

namespace System
{
    SetUnFocusedEvent::SetUnFocusedEvent()
    {
		eventCode = EVENT_SET_UNFOCUSED;
    }

	string SetUnFocusedEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: UNFOCUSED", eventCode);
	}
}
