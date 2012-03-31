#include "point_object.h"
#include "point_object_impl.h"
#include "../../../../math/vec3.h"

namespace OpenGL
{
	PointObject::PointObject()
	{
		impl_vao.reset(new PointObjectImpl());
	}

	PointObject::PointObject(const PointObject& p)
	{
		impl_vao.reset(new PointObjectImpl(static_cast<const PointObjectImpl&>(*p.impl_vao)));
	}

	PointObject& PointObject::operator = (const PointObject& p)
	{
		PointObject temp(p);
		std::swap(impl_vao, temp.impl_vao);
		return *this;
	}

	void PointObject::SetSize(float size)
	{
		static_cast<PointObjectImpl*>(impl_vao.get())->m_size = size;
	}

	void PointObject::SetPosition(const Math::Vector3<float>& pos)
	{
		static_cast<PointObjectImpl*>(impl_vao.get())->m_position = pos;
	}

	void PointObject::Cook()
	{
		struct Vertex 
		{
			float x, y, z, w;
		};
		Vertex vbuffer[1] = {{0, 0, 0, 1}};
		unsigned vbuffer_size = sizeof(Vertex);
		unsigned ibuffer[1] = {0};
		unsigned ibuffer_size = sizeof(unsigned);
		impl_vao->m_primitive_type = GL_POINTS;
		impl_vao->SetVertexBuffer(vbuffer, vbuffer_size, sizeof(Vertex));
		impl_vao->SetIndexBuffer(ibuffer, ibuffer_size);
		impl_vao->Cook(VERTEX_POSITION, GL_POINTS);
	}
}