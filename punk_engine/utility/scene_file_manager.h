#ifndef _H_PUNK_UTILITY_SCENE_MANAGER
#define _H_PUNK_UTILITY_SCENE_MANAGER

#include "config.h"
#include "../system/resource_manager_2.h"
#include "../system/environment.h"
#include "model/punk_scene_loader.h"

namespace System
{
	template<>
	class Policy<Utility::Scene>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.respmd"; }
		static const System::string GetExtension() { return L"*.pmd"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }	
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace Utility
{
	class LIB_UTILITY SceneFileManager : public System::ResourceManager2<Scene, System::Policy>
	{
		SceneFileManager(const SceneFileManager&);
		SceneFileManager& operator = (const SceneFileManager&);		
	};
}

#endif