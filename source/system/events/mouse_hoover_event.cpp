#include "mouse_hoover_event.h"

namespace System
{
    MouseHooverEvent::MouseHooverEvent()
    {
		eventCode = EVENT_MOUSE_HOOVER;
    }

	string MouseHooverEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_HOOVER; x: %d; y: %d; x_prev: %d; y_prev: %d;",
			eventCode, x, y, x_prev, y_prev);
	}
}
