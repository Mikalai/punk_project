#ifndef KEY_MOUSE_LEAVE_EVENT_H
#define KEY_MOUSE_LEAVE_EVENT_H

#include "../../system/events/event.h"
#include "../../system/poolable.h"

namespace GUI
{
	class PUNK_ENGINE_API MouseLeaveEvent : public System::Event, public System::Poolable<MouseLeaveEvent>
    {        
        MouseLeaveEvent(const MouseLeaveEvent&);
		MouseLeaveEvent& operator = (const MouseLeaveEvent&);
    public:
		MouseLeaveEvent();
		virtual System::string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
