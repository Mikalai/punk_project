#include "mouse_enter.h"

namespace GUI
{
    MouseEnterEvent::MouseEnterEvent()
    {
		eventCode = System::EVENT_MOUSE_ENTER;
    }

	System::string MouseEnterEvent::ToString()
	{
        return System::string("Code: {0}; Type: MOUSE_ENTER").arg(eventCode);
	}
}
