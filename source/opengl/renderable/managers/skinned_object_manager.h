#ifndef _H_PUNK_OPENGL_SKINNED_OBJECT_MANAGER
#define _H_PUNK_OPENGL_SKINNED_OBJECT_MANAGER

#include "../../../config.h"
#include "../../../system/resource_manager_2.h"
#include "../../../system/environment.h"
#include "../data/skinned_object.h"

namespace System
{
	template<> class Policy<OpenGL::SkinnedObject>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.res_skinned_vao"; }
		static const System::string GetExtension() { return L"*.skinned_vao"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }	
		static const int GetResourceType() { return System::PERMANENT_RESOURCE_SKINNED_MESH; }
		static void OnInit() {};
		static void OnDestroy() {};
	};
}

namespace OpenGL
{
	class PUNK_ENGINE SkinnedObjectManager : public System::ResourceManager2<SkinnedObject, System::Policy>
	{
		SkinnedObjectManager(const SkinnedObjectManager&);
		SkinnedObjectManager& operator = (const SkinnedObjectManager&);
	};
}

#endif	//	_H_PUNK_OPENGL_STATIC_OBJECT_MANAGER