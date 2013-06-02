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
        return string("Code: {0}; Type: MOUSE_MOVE; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}

}
