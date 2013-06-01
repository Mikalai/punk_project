#include "mouse_wheel_event.h"

namespace System
{
    MouseWheelEvent::MouseWheelEvent()
    {
        eventCode = EVENT_MOUSE_WHEEL;
    }

    string MouseWheelEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_WHEEL; delta: %d; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, delta, x, y, x_prev, y_prev);
	}

}
