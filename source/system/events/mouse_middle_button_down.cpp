#include "mouse_middle_button_down.h"

namespace System
{
    MouseMiddleButtonDownEvent::MouseMiddleButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_DOWN;
    }

	string MouseMiddleButtonDownEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_MBTNDOWN; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}

}
