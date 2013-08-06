#include "../../gl/module.h"
#include "../../../../math/constants.h"
#include "sphere_mesh.h"

namespace GPU
{
	namespace OpenGL
	{
		int64_t SphereObject::VertexCode = Vertex<VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::Tangent,
				VertexComponent::Bitangent,
				VertexComponent::Texture0>::Value();

		std::unique_ptr<SphereObject> SphereObject::m_instance;

		SphereObject* SphereObject::Instance()
		{
			if (!m_instance.get())
			{
				m_instance.reset(new SphereObject);
				m_instance->Cook(1);
			}
			return m_instance.get();
		}

		void SphereObject::Destroy()
		{
			m_instance.reset(nullptr);
		}

		SphereObject::SphereObject() {}

		void SphereObject::Cook(float radius)
		{
			std::vector<CurrentVertex> vb;
			std::vector<unsigned> ib;

			//	around x
			float phi = Math::PI / 2.0f;
			float theta = 0;
			int base = vb.size();
			for (int i = 0; i < 32; ++i)
			{
				ib.push_back(i + base);
				CurrentVertex v;
				v.m_position.Set(radius*cos(phi)*sin(theta), radius*sin(phi)*sin(theta), radius*cos(theta), 1);
				v.m_normal.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
				v.m_texture0.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
				vb.push_back(v);
				theta += 2.0f * Math::PI / 32.0f;
			}

			////	around z
			//phi = 0;
			//theta = Math::PI / 2.0f;
			//base = vb.size();
			//for (int i = 0; i < 32; ++i)
			//{
			//	ib.push_back(i + base);
			//	Vertex<VertexType> v;
			//	v.m_position.Set(radius*cos(phi)*sin(theta), radius*sin(phi)*sin(theta), radius*cos(theta), 1);
			//	v.m_normal.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
			//	v.m_texture0.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
			//	vb.push_back(v);
			//	phi += 2.0f * Math::PI / 32.0f;
			//}

			//	around y
			phi = 0;
			theta = 0;
			base = vb.size();
			for (int i = 0; i < 32; ++i)
			{
				ib.push_back(i + base);
				CurrentVertex v;
				v.m_position.Set(radius*cos(phi)*sin(theta), radius*sin(phi)*sin(theta), radius*cos(theta), 1);
				v.m_normal.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
				v.m_texture0.Set(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta), 1);
				vb.push_back(v);
				theta += 2.0f * Math::PI / 32.0f;
			}

			SetVertexBuffer(vb);
			SetIndexBuffer(ib);
			VertexArrayObject2<PrimitiveType, CurrentVertex>::Cook();
		}
	}
}
