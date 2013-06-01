#include "mouse_middle_button_up.h"

namespace System
{
    MouseMiddleButtonUpEvent::MouseMiddleButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_MBUTTON_UP;
    }

	string MouseMiddleButtonUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_MBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}

}
