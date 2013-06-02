#include "lines.h"

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

#define CreateLineImplementation(VertexType) \
    Lines<VertexType>::Lines(VideoDriver* driver) \
    : impl(new LinesTemplate<VertexType>(driver)) {} \
    Lines<VertexType>::~Lines() { \
    delete impl; impl = nullptr; }\
    void  Lines<VertexType>::Cook(const std::vector<VertexType>& value) {\
    dynamic_cast<LinesTemplate<VertexType>*>(impl)->Cook(value); }\
    void  Lines<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  Lines<VertexType>::Unbind() { \
    impl->Unbind(); }\
    void  Lines<VertexType>::Render() {\
    impl->Render();}

namespace GPU
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using LinesBase = OpenGL::VertexArrayObject2<PrimitiveType::LINES, VertexType>;
#else
#endif	//	USE_OPENGL


    template<typename VertexType>
    class PUNK_ENGINE_API LinesTemplate : public LinesBase<VertexType>
    {
        using Base = LinesBase<VertexType>;

    public:

        LinesTemplate(VideoDriver* driver) : Base(driver) {}

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
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateLineImplementation(VERTEX_1)
#undef VERTEX_1
}
