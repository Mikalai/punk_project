#ifndef _H_PUNK_UTILITY_OBJECT_MANAGER
#define _H_PUNK_UTILITY_OBJECT_MANAGER

#include "../system/resource_manager_2.h"
#include "../system/environment.h"
#include "object.h"
#include "../config.h"

namespace System
{
	template<> class PUNK_ENGINE Policy<Utility::Object>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.robj"; }
		static const System::string GetExtension() { return L"*.object"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }
		static const int GetResourceType() { return System::PERMANENT_RESOURCE_OBJECT; }
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace Utility
{
	class PUNK_ENGINE ObjectManager : public System::ResourceManager2<Object, System::Policy>
	{
		ObjectManager(const ObjectManager&);
		ObjectManager& operator = (const ObjectManager&);
	};
}

#endif	//	_H_PUNK_UTILITY_OBJECT_MANAGER