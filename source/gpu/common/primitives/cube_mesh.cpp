#include "cube_mesh.h"

#ifdef USE_OPENGL
#include "../../opengl/module.h"
#endif

namespace GPU
{
#ifdef USE_OPENGL
    using CubeObjectBase = GPU::OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Tangent,
    VertexComponent::Bitangent,
    VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

    class CubeObject::CubeObjectImpl : public CubeObjectBase
    {
        using Base = CubeObjectBase;
    public:

        CubeObjectImpl(VideoDriver* driver) : Base(driver) {}

        void Cook(float width, float height, float depth)
        {
            std::vector<CurrentVertex> vb(8);
            std::vector<unsigned> ib(36);

            vb[0].m_position.Set(-1.0f, -1.0f, -1.0f, 1.0f);
            vb[0].m_normal.Set( -0.577349f, -0.577349f, -0.577349f, 0);
            vb[0].m_texture0.Set(0, 0, 0, 0);

            vb[1].m_position.Set(-1.0f, 1.0f, -1.0f, 1);
            vb[1].m_normal.Set(-0.577349f,  0.577349f, -0.577349f, 0);
            vb[1].m_texture0.Set(1, 0, 0, 0);

            vb[2].m_position.Set(1.0f,  1.0f, -1.0f, 1);
            vb[2].m_normal.Set( 0.577349f,  0.577349f, -0.577349f, 0);
            vb[2].m_texture0.Set(1, 1, 0, 0);

            vb[3].m_position.Set(1.0f, -1.0f, -1.0f, 1);
            vb[3].m_normal.Set(0.577349f, -0.577349f, -0.577349f, 0);
            vb[3].m_texture0.Set(0, 1, 0, 0);

            vb[4].m_position.Set(-1.0f, -1.0f,  1.0f, 1.0f);
            vb[4].m_normal.Set(-0.577349f, -0.577349f,  0.577349f, 0);
            vb[4].m_texture0.Set(0, 0, 0, 0);

            vb[5].m_position.Set(-1.0f,  1.0f,  1.0f, 1);
            vb[5].m_normal.Set(-0.577349f,  0.577349f,  0.577349f, 0);
            vb[5].m_texture0.Set(1, 0, 0, 0);

            vb[6].m_position.Set(1.0f,  1.0f,  1.0f, 1);
            vb[6].m_normal.Set( 0.577349f,  0.577349f,  0.577349f, 0);
            vb[6].m_texture0.Set(1, 1, 0, 0);

            vb[7].m_position.Set(1.0f, -1.0f,  1.0f, 1);
            vb[7].m_normal.Set(0.577349f, -0.577349f,  0.577349f, 0);
            vb[7].m_texture0.Set(0, 1, 0, 0);

            ib[0] = 4;
            ib[1] = 5;
            ib[2] = 1;
            ib[3] = 5;
            ib[4] = 6;
            ib[5] = 2;
            ib[6] = 6;
            ib[7] = 7;
            ib[8] = 3;
            ib[9] = 7;
            ib[10] = 4;
            ib[11] = 0;
            ib[12] = 0;
            ib[13] = 1;
            ib[14] = 2;
            ib[15] = 7;
            ib[16] = 6;
            ib[17] = 5;
            ib[18] = 0;
            ib[19] = 4;
            ib[20] = 1;
            ib[21] = 1;
            ib[22] = 5;
            ib[23] = 2;
            ib[24] = 2;
            ib[25] = 6;
            ib[26] = 3;
            ib[27] = 3;
            ib[28] = 7;
            ib[29] = 0;
            ib[30] = 3;
            ib[31] = 0;
            ib[32] = 2;
            ib[33] = 4;
            ib[34] = 7;
            ib[35] = 5;

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();
        }
    };

    CubeObject::CubeObject(VideoDriver* driver) : impl(new CubeObjectImpl(driver))
    {}

    CubeObject::~CubeObject()
    {
        delete impl;
        impl = nullptr;
    }

    void CubeObject::Cook(float width, float height, float depth)
    {
        impl->Cook(width, height, depth);
    }

    void CubeObject::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void CubeObject::Unbind()
    {
        impl->Unbind();
    }

    void CubeObject::Render()
    {
        impl->Render();
    }
}
