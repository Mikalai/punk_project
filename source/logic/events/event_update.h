#ifndef _H_PUNK_LOGIC_EVENT_UPDATE
#define _H_PUNK_LOGIC_EVENT_UPDATE

#include "../config.h"
#include "events_type.h"
#include "../../system/events/event.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE EventUpdate : public System::Event
	{
		static std::queue<EventUpdate*> eventPool;
		EventUpdate();
		EventUpdate(const EventUpdate&);
	public:
		double time_in_ms;
		virtual System::string ToString();
		virtual void Release();
		static EventUpdate* Raise();
	};
}

#endif