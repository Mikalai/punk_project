#ifndef IDLE_EVENT_H
#define IDLE_EVENT_H

#include "event.h"

namespace System
{

    class MODULE_SYSTEM IdleEvent : public Event
    {
        static std::queue<IdleEvent*> eventPool;		

        IdleEvent();
        IdleEvent(IdleEvent&);
    public:
		unsigned elapsed_time_ms;
        virtual void Release();
		virtual string ToString();
        static IdleEvent* Raise();
    };	
}

#endif // IDLE_EVENT_H
