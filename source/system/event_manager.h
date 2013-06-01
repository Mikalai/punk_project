/*
	File: EventManager
	Author: Mikalaj Abramau
	Desc: Collects all events that occur in game
*/

#ifndef _H_PUNK_EVENT_MANAGER
#define _H_PUNK_EVENT_MANAGER

#include <queue>
#include <map>
#include "events/events.h"
//#include "monitor.h"
#include "types.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC EventManager
    {	
	private:
		bool m_events_mask[MAX_EVENTS_COUNT];
    public:
		EventManager();

        void SubscribeHandler(long event, Handler handler);
        void UnsubscribeHandler(long event, Handler handler);
        void Process();
        void FixEvent(Event* event);

		void ExcludeFromMonitoring(long message);
		void IncludeInMinutoring(long message);

    private:
        std::queue<Event*> events;
		std::vector<std::vector<Handler> > eventHandlers;
        //Monitor monitor;
    };
};

#endif	//_H_PUNK_EVENT_MANAGER
