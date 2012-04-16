#include "grid_object.h"
#include "grid_object_impl.h"
#include "../../../../common/geometry.h"

namespace OpenGL
{
	GridObject::GridObject()
	{
		impl_vao.reset(new GridObjectImpl());
	}

	GridObject::GridObject(const GridObject& quad)
	{
		impl_vao.reset(new GridObjectImpl(static_cast<const GridObjectImpl&>(*quad.impl_vao)));
	}

	GridObject& GridObject::operator = (const GridObject& quad)
	{
		GridObject temp(quad);
		std::swap(impl_vao, temp.impl_vao);
		return *this;
	}

	void GridObject::SetHeight(float height)
	{
		static_cast<GridObjectImpl*>(impl_vao.get())->m_height = height;
	}

	void GridObject::SetWidth(float width)
	{
		static_cast<GridObjectImpl*>(impl_vao.get())->m_width = width;
	}

	void GridObject::SetHeightSlice(unsigned height)
	{
		static_cast<GridObjectImpl*>(impl_vao.get())->m_height_slice = height;
	}

	void GridObject::SetWidthSlice(unsigned width)
	{
		static_cast<GridObjectImpl*>(impl_vao.get())->m_width_slice = width;
	}

	void GridObject::Cook()
	{
		GridObjectImpl& impl = static_cast<GridObjectImpl&>(*impl_vao);
		struct Vertex
		{
			float x, y, z, w;
			float nx, ny, nz, nw;
			float u, v, s, t;
			float ix, iy, iz, iw;
		};

		std::vector<Vertex> v((impl.m_width_slice+1)*(impl.m_height_slice+1));
		for (int i = 0; i < impl.m_height_slice + 1; i++)
		{
			for (int j = 0; j < impl.m_width_slice + 1; j++)
			{
				v[i*(impl.m_width_slice+1) + j].x = impl.m_width/float(impl.m_width_slice)*float(j);
				v[i*(impl.m_width_slice+1) + j].y = 0;
				v[i*(impl.m_width_slice+1) + j].z = impl.m_height/float(impl.m_height_slice)*float(i);
				v[i*(impl.m_width_slice+1) + j].nx = v[i*(impl.m_width_slice+1) + j].nz = 0;
				v[i*(impl.m_width_slice+1) + j].ny = 1.0f;
				v[i*(impl.m_width_slice+1) + j].u = 1.0f/float(impl.m_width_slice)*float(j);
				v[i*(impl.m_width_slice+1) + j].v = 1.0f/float(impl.m_height_slice)*float(i);
				v[i*(impl.m_width_slice+1) + j].ix = (i + j) % 2;
			}
		}

		std::vector<unsigned int> index(6*impl.m_width_slice*impl.m_height_slice);

		for (int i = 0; i < impl.m_height_slice; i++)
		{
			for (int j = 0; j < impl.m_width_slice; j++)
			{
				index[6*(i*impl.m_width_slice + j) + 0] = i*(impl.m_width_slice+1) + j + 0;
				index[6*(i*impl.m_width_slice + j) + 1] = (i+1)*(impl.m_width_slice+1) + j;
				index[6*(i*impl.m_width_slice + j) + 2] = i*(impl.m_width_slice+1) + j + 1;					

				index[6*(i*impl.m_width_slice + j) + 3] = i*(impl.m_width_slice+1) + j + 1;
				index[6*(i*impl.m_width_slice + j) + 4] = (i+1)*(impl.m_width_slice+1) + j;
				index[6*(i*impl.m_width_slice + j) + 5] = (i+1)*(impl.m_width_slice+1) + j + 1;
			}
		}

		unsigned vbuffer_size = v.size()*sizeof(Vertex);		
		unsigned ibuffer_size = index.size()*sizeof(unsigned);
		impl_vao->SetVertexBuffer(&v[0], vbuffer_size, sizeof(Vertex));
		impl_vao->SetIndexBuffer(&index[0], ibuffer_size);
		impl_vao->Cook(VERTEX_POSITION|VERTEX_TEXTURE_0|VERTEX_FLAGS|VERTEX_NORMAL, GL_TRIANGLES);/**/
	}
}