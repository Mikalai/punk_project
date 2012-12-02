#ifndef _H_PUNK_SYSTEM_RESOURCE_CREATOR
#define _H_PUNK_SYSTEM_RESOURCE_CREATOR

#include "smart_pointers/proxy.h"
#include "object.h"

namespace System
{
	class ResourceCreator
	{
	public:
		virtual Proxy<Object> Create() = 0;
		virtual Proxy<Object> Create(const string& name) = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_RESOURCE_CREATOR