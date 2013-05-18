

#include "quad_mesh.h"

namespace GPU
{
	namespace OpenGL
	{
		std::unique_ptr<QuadObject> QuadObject::m_instance;

		QuadObject* QuadObject::Instance()
		{
			if (!m_instance.get())
			{
				m_instance.reset(new QuadObject);
				m_instance->Cook(1,1);
			}
			return m_instance.get();
		}

		void QuadObject::Destroy()
		{
			m_instance.reset(nullptr);
		}

		QuadObject::QuadObject() {}

		void QuadObject::Cook(float width, float height)
		{
			std::vector<CurrentVertex> vb(4);
			std::vector<unsigned> ib(6);

			vb[0].m_position.Set(0, 0, 0, 1);
			vb[0].m_normal.Set(0, 0, 1, 0);
			vb[0].m_texture0.Set(0, 0, 0, 0);

			vb[1].m_position.Set(width, 0, 0, 1);
			vb[1].m_normal.Set(0, 0, 1, 0);
			vb[1].m_texture0.Set(1, 0, 0, 0);

			vb[2].m_position.Set(width, height, 0, 1);
			vb[2].m_normal.Set(0, 0, 1, 0);
			vb[2].m_texture0.Set(1, 1, 0, 0);

			vb[3].m_position.Set(0, height, 0, 1);
			vb[3].m_normal.Set(0, 0, 1, 0);
			vb[3].m_texture0.Set(0, 1, 0, 0);

			ib[0] = 0;
			ib[1] = 1;
			ib[2] = 2;
			ib[3] = 0;
			ib[4] = 2;
			ib[5] = 3;

			SetVertexBuffer(vb);
			SetIndexBuffer(ib);
			VertexArrayObject2<PrimitiveType, CurrentVertex>::Cook();
		}
	}
}
