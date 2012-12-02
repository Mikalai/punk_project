#ifndef _H_PUNK_UTILITY_ARAMTURE_MANAGER
#define _H_PUNK_UTILITY_ARAMTURE_MANAGER

#include "../../config.h"
#include "../../system/resource_manager_2.h"
#include "../../system/environment.h"
#include "armature.h"

namespace System
{
	template<>	class Policy<Virtual::Armature>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.armature"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetArmatureFolder(); }
		static System::ObjectType GetResourceType() { return System::ObjectType::ARMATURE; }
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace Virtual
{
	class ArmatureManager : public System::ResourceManager2<Armature, System::Policy>
	{
		ArmatureManager(const ArmatureManager&);
		ArmatureManager& operator = (const ArmatureManager&);
	};
}

#endif	//	_H_PUNK_UTILITY_ARAMTURE_MANAGER