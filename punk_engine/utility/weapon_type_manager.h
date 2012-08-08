#ifndef _H_PUNK_UTILITY_WEAPON_TYPE_MANAGER
#define _H_PUNK_UTILITY_WEAPON_TYPE_MANAGER

#include <vector>
#include <memory>
#include <iostream>

#include "config.h"
#include "weapon_type.h"

#include "../system/resource_manager_2.h"
#include "../system/environment.h"

namespace System { class string; }

namespace System
{
	template<> class LIB_UTILITY Policy<Utility::WeaponType>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.weapon"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetWeaponFolder(); }	
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace Utility
{		

	class LIB_UTILITY WeaponTypeManager : public System::ResourceManager2<WeaponType, System::Policy>
	{
		WeaponTypeManager(const WeaponTypeManager&);
		WeaponTypeManager& operator = (const WeaponTypeManager&);		
	};
}

#endif	//	_H_PUNK_UTILITY_WEAPON_TYPE_MANAGER