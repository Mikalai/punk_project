#include "mouse_enter.h"

namespace GUI
{
    MouseEnterEvent::MouseEnterEvent()
    {
		eventCode = System::EVENT_MOUSE_ENTER;
    }

	System::string MouseEnterEvent::ToString()
	{
		return System::string::Format(L"Code: %d; Type: MOUSE_ENTER",
			eventCode);
	}
}
