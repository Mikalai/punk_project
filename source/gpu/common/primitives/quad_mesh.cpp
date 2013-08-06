#include "quad_mesh.h"

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace Gpu
{
#ifdef USE_OPENGL
    using QuadObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL


    class QuadObject::QuadObjectImpl : public QuadObjectBase
    {
        using Base = QuadObjectBase;
    public:
        QuadObjectImpl(VideoDriver* driver) : Base(driver)
        {}

        void Cook(float width, float height)
        {
            Base::Clear();

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

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();
        }
    };

    QuadObject::QuadObject(VideoDriver *driver)
        : impl(new QuadObject::QuadObjectImpl(driver))
    {}

    QuadObject::~QuadObject()
    {
        delete impl;
        impl = nullptr;
    }

    void QuadObject::Cook(float width, float height)
    {
        impl->Cook(width, height);
    }

    void QuadObject::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void QuadObject::Unbind()
    {
        impl->Unbind();
    }

    void QuadObject::Render()
    {
        impl->Render();
    }
}
