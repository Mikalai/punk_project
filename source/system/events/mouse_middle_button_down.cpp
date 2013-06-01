#include "mouse_middle_button_down.h"

namespace System
{
    MouseMiddleButtonDownEvent::MouseMiddleButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_DOWN;
    }

	string MouseMiddleButtonDownEvent::ToString()
	{
		return string("Code: %d; Type: MOUSE_MBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
