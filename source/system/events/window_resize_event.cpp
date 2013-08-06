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
        return string("Code: {0}; Type: RESIZE; Width: {1}; Height: {2}; Minimized: {3}; Restored: {4}")
                .arg(eventCode).arg(width).arg(height).arg(minimized ? L"TRUE" : L"FALSE").arg(restored ? L"TRUE" : L"FALSE");
	}
}
