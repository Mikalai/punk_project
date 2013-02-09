#ifndef KEY_MOUSE_ENTER_EVENT_H
#define KEY_MOUSE_ENTER_EVENT_H

#include "../../system/events/event.h"
#include "../../system/poolable.h"

namespace GUI
{
	class PUNK_ENGINE MouseEnterEvent : public System::Event, public System::Poolable<MouseEnterEvent>
    {        
        MouseEnterEvent(const MouseEnterEvent&);
    public:
		MouseEnterEvent();
		virtual System::string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
