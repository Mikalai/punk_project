#ifndef _H_PUNK_OPENGL_QUAD_OBJECT_IMPL
#define _H_PUNK_OPENGL_QUAD_OBJECT_IMPL

#include "vertext_array_object_impl.h"
#include "../../../../math/vec3.h"

namespace OpenGL
{
	struct QuadObjectImpl : public VertexArrayObjectImpl
	{
		float m_width;
		float m_height;

		QuadObjectImpl()
			: VertexArrayObjectImpl()
			, m_width(1)
			, m_height(1)
		{}

		QuadObjectImpl(const QuadObjectImpl& impl)
			: VertexArrayObjectImpl(impl)
			, m_width(impl.m_width)
			, m_height(impl.m_height)
		{}
	};
}

#endif