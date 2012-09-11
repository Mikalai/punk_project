#ifndef IDLE_EVENT_H
#define IDLE_EVENT_H

#include "event.h"

namespace System
{

    class PUNK_ENGINE IdleEvent : public Event
    {
        static std::queue<IdleEvent*> eventPool;		

        IdleEvent();
        IdleEvent(IdleEvent&);
    public:
		double elapsed_time_s;
        virtual void Release();
		virtual string ToString();
        static IdleEvent* Raise();
    };	
}

#endif // IDLE_EVENT_H
