#include "mouse_enter.h"

namespace System
{
    MouseEnterEvent::MouseEnterEvent()
    {
		eventCode = EVENT_MOUSE_ENTER;
    }

	string MouseEnterEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_ENTER",
			eventCode);
	}
}
