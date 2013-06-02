#include "triangles.h"

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

#define CreateTrianglesImplementation(VertexType) \
    Triangles<VertexType>::Triangles(VideoDriver* driver) \
    : impl(new TrianglesTemplate<VertexType>(driver)) {} \
    Triangles<VertexType>::~Triangles<VertexType>() { \
    delete impl; impl = nullptr; }\
    void  Triangles<VertexType>::Cook(const std::vector<VertexType>& value) {\
    dynamic_cast<TrianglesTemplate<VertexType>*>(impl)->Cook(value); }\
    void  Triangles<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  Triangles<VertexType>::Unbind() { \
impl->Unbind(); }\
void  Triangles<VertexType>::Render() {\
    impl->Render();}


namespace GPU
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using TrianglesBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, VertexType>;
#else
#endif

    template<typename VertexType>
    class TrianglesTemplate: public TrianglesBase<VertexType>
    {
        using Base = TrianglesBase<VertexType>;

    public:

        TrianglesTemplate(VideoDriver* driver) : Base(driver) {}

        void Cook(const std::vector<VertexType>& value)
        {
            Base::Clear();
            std::vector<unsigned> ib(value.size());
            for (unsigned i = 0; i < ib.size(); ++i)
                ib[i] = i;
            Base::SetVertexBuffer(value);
            Base::SetIndexBuffer(ib);
            Base::Cook();
        }
    };

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1
}
