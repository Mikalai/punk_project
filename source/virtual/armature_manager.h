#ifndef _H_PUNK_UTILITY_ARAMTURE_MANAGER
#define _H_PUNK_UTILITY_ARAMTURE_MANAGER

#include "../config.h"
#include "../system/resource_manager_2.h"
#include "../system/environment.h"
#include "armature.h"

namespace System
{
	template<>	class Policy<Utility::Armature>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.armature"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetArmatureFolder(); }
		static const int GetResourceType() { return System::PERMANENT_RESOURCE_ARMATURE; }
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace Utility
{
	class ArmatureManager : public System::ResourceManager2<Armature, System::Policy>
	{
		ArmatureManager(const ArmatureManager&);
		ArmatureManager& operator = (const ArmatureManager&);
	};
}

#endif	//	_H_PUNK_UTILITY_ARAMTURE_MANAGER