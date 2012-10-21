#include "mouse_leave.h"

namespace System
{
    MouseLeaveEvent::MouseLeaveEvent()
    {
		eventCode = EVENT_MOUSE_LEAVE;
    }

	string MouseLeaveEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LEAVE;");
	}
}
