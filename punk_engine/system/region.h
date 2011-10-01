#ifndef _H_PUNK_REGION
#define _H_PUNK_REGION

#include <map>
#include "handler.h"
#include "event_manager.h"

namespace System
{
	class Region
	{
		typedef unsigned ObjectType;
		typedef unsigned InstanceNumber;
		Handler m_handler;
		typedef std::map<ObjectType, std::multimap<InstanceNumber, Handler>> m_region;
	public:

		void BuildFromMemory();
		bool HasObject(const Handler& h) const;

		void OnInstanceChangedPosition(Event* event);
		void OnInstanceChangedParent(Event* event);
	};
}

#endif