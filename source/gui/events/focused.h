#ifndef SET_FOCUSED_EVENT_H
#define SET_FOCUSED_EVENT_H

#include "../../system/events/event.h"
#include "../../system/poolable.h"

namespace GUI
{
	class PUNK_ENGINE SetFocusedEvent : public System::Event, public System::Poolable<SetFocusedEvent>
    {        
        SetFocusedEvent(const SetFocusedEvent&);
		SetFocusedEvent& operator = (const SetFocusedEvent&);
    public:
		SetFocusedEvent();
		virtual System::string ToString();
    };
}

#endif // SET_FOCUSED_EVENT_H
