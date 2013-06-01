#include "mouse_right_button_down.h"

namespace System
{
    MouseRightButtonDownEvent::MouseRightButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_DOWN;
    }

	string MouseRightButtonDownEvent::ToString()
	{
		return string("Code: %d; Type: MOUSE_RBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
