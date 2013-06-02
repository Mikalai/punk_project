#include "mouse_right_button_down.h"

namespace System
{
    MouseRightButtonDownEvent::MouseRightButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_DOWN;
    }

	string MouseRightButtonDownEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_RBTNDOWN; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
