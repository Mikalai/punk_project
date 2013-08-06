#include "mouse_left_button_down.h"

namespace System
{
    MouseLeftButtonDownEvent::MouseLeftButtonDownEvent()
    {
        eventCode = EVENT_MOUSE_LBUTTON_DOWN;
    }

	string MouseLeftButtonDownEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_LBTNDOWN; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
