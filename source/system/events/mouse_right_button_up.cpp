#include "mouse_right_button_up.h"

namespace System
{
    MouseRightButtonUpEvent::MouseRightButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_RBUTTON_UP;
    }

	string MouseRightButtonUpEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_RBTNUP; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
