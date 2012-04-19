#ifndef _H_PUNK_OPENGL_STATIC_OBJECT_IMPL
#define _H_PUNK_OPENGL_STATIC_OBJECT_IMPL

#include "vertext_array_object_impl.h"

namespace Utility
{
	class StaticMesh;
}

namespace OpenGL
{
	struct StaticObjectImpl : public VertexArrayObjectImpl
	{
		Utility::StaticMesh* m_object;
	
		StaticObjectImpl()
			: VertexArrayObjectImpl()
			, m_object(0)
		{}

		StaticObjectImpl(const StaticObjectImpl& impl)
			: VertexArrayObjectImpl(impl)
			, m_object(impl.m_object)
		{}
	};
}
#endif