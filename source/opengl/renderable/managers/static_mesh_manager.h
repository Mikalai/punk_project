#ifndef _H_PUNK_OPENGL_STATIC_OBJECT_MANAGER
#define _H_PUNK_OPENGL_STATIC_OBJECT_MANAGER

#include "../../../config.h"
#include "../../../system/resource_manager_2.h"
#include "../../../system/environment.h"
#include "../primitives/static_mesh.h"

namespace System
{
	template<> class Policy<OpenGL::StaticMesh>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.res_static_vao"; }
		static const System::string GetExtension() { return L"*.static_vao"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }	
		static const int GetResourceType() { return System::PERMANENT_RESOURCE_STATIC_MESH; }
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace OpenGL
{
	class PUNK_ENGINE StaticMeshManager : public System::ResourceManager2<StaticMesh, System::Policy>
	{
		StaticMeshManager(const StaticMeshManager&);
		StaticMeshManager& operator = (const StaticMeshManager&);
	};	
}

#endif	//	_H_PUNK_OPENGL_STATIC_OBJECT_MANAGER