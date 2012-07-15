#ifndef _H_PUNK_UTILITY_SCENE_MANAGER
#define _H_PUNK_UTILITY_SCENE_MANAGER

#include "config.h"
#include "../system/resource_manager_2.h"
#include "model\punk_scene_loader.h"

namespace System
{
	template<>
	class Policy<Utility::Scene>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*."; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetSoundFolder(); }	
		static void OnInit();
		static void OnDestroy();
	};
}

namespace Utility
{

}

#endif