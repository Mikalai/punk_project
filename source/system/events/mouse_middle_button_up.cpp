#include "mouse_middle_button_up.h"

namespace System
{
    MouseMiddleButtonUpEvent::MouseMiddleButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_UP;
    }

	string MouseMiddleButtonUpEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_MBTNUP; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}

}
