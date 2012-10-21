#include "window_resize_event.h"

namespace System
{

    WindowResizeEvent::WindowResizeEvent()
    {
		eventCode = EVENT_WINDOW_RESIZE;
    }

	WindowResizeEvent::~WindowResizeEvent()
	{}

	string WindowResizeEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: RESIZE; Width: %d; Height: %d; Minimized: %s; Restored: %s",
			eventCode, width, height, minimized ? L"TRUE" : L"FALSE", restored ? L"TRUE" : L"FALSE");
	}
}
