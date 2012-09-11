#ifndef _H_VAO_MANAGER
#define _H_VAO_MANAGER

#include "../config.h"
#include "../system/resource_manager_2.h"
#include "../system/environment.h"
#include "vertex_array_object.h"

namespace System
{
	template<> class Policy<OpenGL::VertexArrayObject>
	{
	public:
		static const System::string GetResourceFile() { return L"resource.resvao"; }
		static const System::string GetExtension() { return L"*.vao"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetModelFolder(); }	
		static void OnInit();
		static void OnDestroy();
	};
}

namespace OpenGL
{
	class PUNK_ENGINE VaoManager : public System::ResourceManager2<VertexArrayObject, System::Policy>
	{
		VaoManager(const VaoManager&);
		VaoManager& operator = (const VaoManager&);
	};
}

#endif	//	_H_VAO_MANAGER