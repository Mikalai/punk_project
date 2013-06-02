#include "grid_object.h"

#ifdef USE_OPENGL
#include "../../opengl/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{    
#ifdef USE_OPENGL
    using GridObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Texture0,
    VertexComponent::Flag>>;
#else
#endif

    class GridObject::GridObjectImpl : public GridObjectBase
    {
        using Base = GridObjectBase;

    public:

        GridObjectImpl(VideoDriver* driver) : Base(driver) {}

        void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices)
        {
            std::vector<CurrentVertex> v((hor_slices+1)*(vert_slices+1));
            for (int i = 0; i < (int)vert_slices + 1; i++)
            {
                for (int j = 0; j < (int)hor_slices + 1; j++)
                {
                    v[i*(hor_slices+1) + j].m_position.Set(
                                width/float(hor_slices)*float(j),
                                0,
                                height/float(vert_slices)*float(i),
                                1);

                    v[i*(hor_slices+1) + j].m_normal.Set(0, 1.0f, 0, 0);

                    v[i*(hor_slices+1) + j].m_texture0.Set(
                                1.0f/float(hor_slices)*float(j),
                                1.0f/float(vert_slices)*float(i), 0, 0);

                    if (i == 0 || j == 0 || i == vert_slices || j == hor_slices)
                        v[i*(hor_slices+1) + j].m_flag.Set(float((i + j) % 2), 0, 0, 0);
                    else
                        v[i*(hor_slices+1) + j].m_flag.Set(float((i + j) % 2), 0, 0, 0);
                }
            }

            std::vector<unsigned int> index(6*hor_slices*vert_slices);

            for (int i = 0; i < (int)vert_slices; i++)
            {
                for (int j = 0; j < (int)hor_slices; j++)
                {
                    index[6*(i*hor_slices + j) + 0] = i*(hor_slices+1) + j + 0;
                    index[6*(i*hor_slices + j) + 1] = (i+1)*(hor_slices+1) + j;
                    index[6*(i*hor_slices + j) + 2] = i*(hor_slices+1) + j + 1;

                    index[6*(i*hor_slices + j) + 3] = i*(hor_slices+1) + j + 1;
                    index[6*(i*hor_slices + j) + 4] = (i+1)*(hor_slices+1) + j;
                    index[6*(i*hor_slices + j) + 5] = (i+1)*(hor_slices+1) + j + 1;
                }
            }

            Base::SetVertexBuffer(v);
            Base::SetIndexBuffer(index);
            Base::Cook();/**/
        }
    };


    GridObject::GridObject(VideoDriver* driver) : impl(new GridObjectImpl(driver)) {}

    GridObject::~GridObject()
    {
        delete impl;
        impl = nullptr;
    }

    void GridObject::Cook(float width, float height, unsigned hor_slices, unsigned vert_slices)
    {
        impl->Cook(width, height, hor_slices, vert_slices);
    }

    void GridObject::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void GridObject::Unbind()
    {
        impl->Unbind();
    }

    void GridObject::Render()
    {
        impl->Render();
    }
}
