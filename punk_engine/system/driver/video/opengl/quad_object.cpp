#include "quad_object.h"
#include "quad_object_impl.h"

namespace OpenGL
{
	QuadObject::QuadObject()
	{
		impl_vao.reset(new QuadObjectImpl());
	}

	QuadObject::QuadObject(const QuadObject& quad)
	{
		impl_vao.reset(new QuadObjectImpl(static_cast<const QuadObjectImpl&>(*quad.impl_vao)));
	}

	QuadObject& QuadObject::operator = (const QuadObject& quad)
	{
		QuadObject temp(quad);
		std::swap(impl_vao, temp.impl_vao);
		return *this;
	}

	void QuadObject::SetHeight(float height)
	{
		static_cast<QuadObjectImpl*>(impl_vao.get())->m_height = height;
	}

	void QuadObject::SetWidth(float width)
	{
		static_cast<QuadObjectImpl*>(impl_vao.get())->m_width = width;
	}

	void QuadObject::Cook()
	{
		struct LocalVertex
		{
			float x, y, z, w;
			float u, v, s, t;
		};

		std::vector<LocalVertex> vbuffer(4);
		float z = 0;
		vbuffer[0].x = -0.5;	vbuffer[0].y = -0.5;	vbuffer[0].z = z; vbuffer[0].w = 1;
		vbuffer[0].u = 0;		vbuffer[0].v = 1;		vbuffer[0].s = 0; vbuffer[0].t = 1;
		vbuffer[1].x = 0.5;		vbuffer[1].y = -0.5;	vbuffer[1].z = z; vbuffer[1].w = 1;
		vbuffer[1].u = 1;		vbuffer[1].v = 1;		vbuffer[1].s = 0; vbuffer[1].t = 1;
		vbuffer[2].x = 0.5;		vbuffer[2].y = 0.5;		vbuffer[2].z = z; vbuffer[2].w = 1;
		vbuffer[2].u = 1;		vbuffer[2].v = 0;		vbuffer[2].s = 0; vbuffer[2].t = 1;
		vbuffer[3].x = -0.5;	vbuffer[3].y = 0.5;		vbuffer[3].z = z; vbuffer[3].w = 1;
		vbuffer[3].u = 0;		vbuffer[3].v = 0;		vbuffer[3].s = 0; vbuffer[3].t = 1;
		unsigned vbuffer_size = 4*sizeof(LocalVertex);
		unsigned ibuffer[6] = { 0, 1, 2, 2, 3, 0};
		unsigned ibuffer_size = sizeof(ibuffer);
		impl_vao->SetVertexBuffer(&vbuffer[0], vbuffer_size, sizeof(LocalVertex));
		impl_vao->SetIndexBuffer(ibuffer, ibuffer_size);
		impl_vao->Cook(VERTEX_POSITION|VERTEX_TEXTURE_0, GL_TRIANGLES);
	}
}