#include "mouse_leave.h"

namespace GUI
{
    MouseLeaveEvent::MouseLeaveEvent()
    {
		eventCode = System::EVENT_MOUSE_LEAVE;
    }

	System::string MouseLeaveEvent::ToString()
	{
		return System::string::Format(L"Code: %d; Type: MOUSE_LEAVE;");
	}
}
