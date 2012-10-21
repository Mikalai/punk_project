#ifndef KEY_MOUSE_ENTER_EVENT_H
#define KEY_MOUSE_ENTER_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE MouseEnterEvent : public Event, public Poolable<MouseEnterEvent>
    {        
        MouseEnterEvent(const MouseEnterEvent&);
    public:
		MouseEnterEvent();
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
