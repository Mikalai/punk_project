#include "mouse_left_button_down.h"

namespace System
{
    MouseLeftButtonDownEvent::MouseLeftButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_LBUTTON_DOWN;
    }

	string MouseLeftButtonDownEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LBTNDOWN; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
