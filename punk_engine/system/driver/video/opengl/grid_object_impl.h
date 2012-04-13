#ifndef _H_PUNK_OPENGL_GRID_OBJECT_IMPL
#define _H_PUNK_OPENGL_GRID_OBJECT_IMPL

#include "vertext_array_object_impl.h"

namespace OpenGL
{
	struct GridObjectImpl : public VertexArrayObjectImpl
	{
		float m_width;
		float m_height;
		unsigned m_width_slice;
		unsigned m_height_slice;
	
		GridObjectImpl()
			: VertexArrayObjectImpl()
			, m_width(1)
			, m_height(1)
			, m_width_slice(0)
			, m_height_slice(0)
		{}

		GridObjectImpl(const GridObjectImpl& impl)
			: VertexArrayObjectImpl(impl)
			, m_width(impl.m_width)
			, m_height(impl.m_height)
		{}
	};
}
#endif