#include "mouse_right_button_up.h"

namespace System
{
    MouseRightButtonUpEvent::MouseRightButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_UP;
    }

	string MouseRightButtonUpEvent::ToString()
	{
		return string("Code: %d; Type: MOUSE_RBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
