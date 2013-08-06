#include "sphere_mesh.h"

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace Gpu
{

#ifdef USE_OPENGL
    using SphereObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::LINE_LOOP,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Tangent,
    VertexComponent::Bitangent,
    VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

    class SphereObject::SphereObjectImpl : public SphereObjectBase
    {
        using Base = SphereObjectBase;

    public:
        SphereObjectImpl(VideoDriver* driver) : Base(driver) {}
        void Cook(float radius)
        {
            Base::Clear();

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

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();
        }
    };

	SphereObject::SphereObject(VideoDriver *driver)
        : impl(new SphereObjectImpl(driver))
    {}

    SphereObject::~SphereObject()
    {
        delete impl;
        impl = nullptr;
    }

	void SphereObject::Cook(float radius)
	{
        impl->Cook(radius);
	}

    void SphereObject::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void SphereObject::Unbind()
    {
        impl->Unbind();
    }

    void SphereObject::Render()
    {
        impl->Render();
    }
}
