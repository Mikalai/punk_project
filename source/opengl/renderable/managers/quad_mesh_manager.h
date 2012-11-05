#ifndef _H_PUNK_OPENGL_QUAD_OBJECT_MANAGER
#define _H_PUNK_OPENGL_QUAD_OBJECT_MANAGER

#include "../../../config.h"
#include "../../../system/resource_manager_2.h"
#include "../../../system/environment.h"
#include "../primitives/quad_mesh.h"

namespace System
{
	template<> class Policy<OpenGL::QuadObject>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.res_quad_vao"; }
		static const System::string GetExtension() { return L"*.quad_vao"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }	
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace OpenGL
{
	class PUNK_ENGINE QuadObjectManager : public System::ResourceManager2<StaticMesh, System::Policy>
	{
		QuadObjectManager(const QuadObjectManager&);
		QuadObjectManager& operator = (const QuadObjectManager&);
	};
}

#endif	//	_H_PUNK_OPENGL_STATIC_OBJECT_MANAGER