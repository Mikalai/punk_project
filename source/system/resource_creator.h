#ifndef _H_PUNK_SYSTEM_RESOURCE_CREATOR
#define _H_PUNK_SYSTEM_RESOURCE_CREATOR

#include "smart_pointers/proxy.h"
#include "object.h"

namespace System
{
	class PUNK_ENGINE ResourceCreator
	{
	public:
		virtual Object* Create() = 0;
		virtual Object* Create(const string& name) = 0;
		virtual bool Init() = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_RESOURCE_CREATOR