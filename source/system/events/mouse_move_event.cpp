#include "mouse_move_event.h"

namespace System
{
    MouseMoveEvent::MouseMoveEvent()
    {
        eventCode = EVENT_MOUSE_MOVE;
		x = y = x_prev = y_prev = 0;
		controlKey = leftButton = middleButton =
				rightButton = shiftButton =
				xbutton1 = xbutton2 = false;
    }

	string MouseMoveEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_MOVE; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
