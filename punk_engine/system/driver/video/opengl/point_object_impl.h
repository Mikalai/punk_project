#ifndef _H_PUNK_OPENGL_MODULE_POINT_OBJECT_IMPL
#define _H_PUNK_OPENGL_MODULE_POINT_OBJECT_IMPL

#include "vertext_array_object_impl.h"
#include "../../../../math/vec3.h"

namespace OpenGL
{
	struct PointObjectImpl : public VertexArrayObjectImpl
	{
		float m_size;
		Math::vec3 m_position;
	
		PointObjectImpl() 
			: VertexArrayObjectImpl()
			, m_size(1)
			, m_position()
		{}

		PointObjectImpl(const PointObjectImpl& po)
			: VertexArrayObjectImpl(po)
			, m_size(po.m_size)
			, m_position(po.m_position)
		{}
	};	
}

#endif