#ifndef _H_PUNK_WINDOW_RESIZE
#define _H_PUNK_WINDOW_RESIZE

#include "event.h"
#include "../poolable.h"

namespace System
{
	class PUNK_ENGINE_API WindowResizeEvent : public Event, public Poolable<WindowResizeEvent>
    {        
        WindowResizeEvent(const WindowResizeEvent&);
    public:
		WindowResizeEvent();
		virtual ~WindowResizeEvent();

        bool minimized;
		bool restored;
        int width, height;
		
		virtual string ToString();
    };
}

#endif