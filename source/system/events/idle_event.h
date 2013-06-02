#ifndef IDLE_EVENT_H
#define IDLE_EVENT_H

#include "event.h"
#include "../poolable.h"

namespace System
{

    class PUNK_ENGINE_API IdleEvent : public Event, public Poolable<IdleEvent>
    {        
        IdleEvent(IdleEvent&);
    public:
		IdleEvent();		
		double elapsed_time_s;
		virtual string ToString();
    };	
}

#endif // IDLE_EVENT_H
