#include "mouse_left_button_up.h"

namespace System
{
    MouseLeftButtonUpEvent::MouseLeftButtonUpEvent()
    {
        eventCode = EVENT_MOUSE_LBUTTON_UP;
    }

	string MouseLeftButtonUpEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MOUSE_LBTNUP; x: %d; y: %d; x_prev: %d; y_prev: %d;",
							   eventCode, x, y, x_prev, y_prev);
	}
}
