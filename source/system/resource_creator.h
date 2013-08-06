#ifndef _H_PUNK_SYSTEM_RESOURCE_CREATOR
#define _H_PUNK_SYSTEM_RESOURCE_CREATOR

#include "smart_pointers/proxy.h"
#include "object.h"

namespace System
{
	class PUNK_ENGINE_API ResourceCreator
	{
	public:
		virtual Object* Create() override;
		virtual Object* Create(const string& name) override;
		virtual bool Init() override;
	};
}

#endif	//	_H_PUNK_SYSTEM_RESOURCE_CREATOR