#include "window_resize_event.h"

namespace System
{
    std::queue<WindowResizeEvent*> WindowResizeEvent::eventPool;

    WindowResizeEvent::WindowResizeEvent()
    {
		eventCode = EVENT_WINDOW_RESIZE;
    }

    void WindowResizeEvent::Release()
    {
        this->eventPool.push(this);
    }

    WindowResizeEvent* WindowResizeEvent::Raise()
    {
        if (eventPool.empty())
        {
            WindowResizeEvent* event = new WindowResizeEvent();
            return event;
        }
        else
        {
            WindowResizeEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string WindowResizeEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: RESIZE; Width: %d; Height: %d; Minimized: %s; Restored: %s",
			eventCode, width, height, minimized ? L"TRUE" : L"FALSE", restored ? L"TRUE" : L"FALSE");
	}
}
