#ifndef SET_UNFOCUSED_EVENT_H
#define SET_UNFOCUSED_EVENT_H

#include "../../system/events/event.h"
#include "../../system/poolable.h"

namespace GUI
{
	class PUNK_ENGINE_API SetUnFocusedEvent : public System::Event, public System::Poolable<SetUnFocusedEvent>
    {        
        SetUnFocusedEvent(const SetUnFocusedEvent&);
		SetUnFocusedEvent& operator = (const SetUnFocusedEvent&);
    public:
		SetUnFocusedEvent();
		virtual System::string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
