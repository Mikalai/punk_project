#include "mouse_wheel_event.h"

namespace System
{
    MouseWheelEvent::MouseWheelEvent()
    {
        eventCode = EVENT_MOUSE_WHEEL;
    }

    string MouseWheelEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_WHEEL; delta: {1}; x: {2}; y: {3}; x_prev: {4}; y_prev: {5};")
                .arg(eventCode).arg(delta).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}

}
