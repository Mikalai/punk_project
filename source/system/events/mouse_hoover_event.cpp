#include "mouse_hoover_event.h"

namespace System
{
    MouseHooverEvent::MouseHooverEvent()
    {
		eventCode = EVENT_MOUSE_HOOVER;
    }

	string MouseHooverEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_HOOVER; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
