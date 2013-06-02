#include "points.h"

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

#define CreatePointImplementation(VertexType) \
    Points<VertexType>::Points(VideoDriver* driver) \
    : impl(new PointsTemplate<VertexType>(driver)) {} \
    Points<VertexType>::~Points(){ \
    delete impl; impl = nullptr; }\
    void  Points<VertexType>::Cook(const std::vector<VertexType>& value) {\
    dynamic_cast<PointsTemplate<VertexType>*>(impl)->Cook(value); }\
    void  Points<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  Points<VertexType>::Unbind() { \
impl->Unbind(); }\
void  Points<VertexType>::Render() {\
    impl->Render();}


namespace GPU
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using PointsBase = OpenGL::VertexArrayObject2<PrimitiveType::POINTS, VertexType>;
#else
#endif

    template<typename VertexType>
    class PUNK_ENGINE_API PointsTemplate : public PointsBase<VertexType>
    {
        using Base = PointsBase<VertexType>;

    public:

        PointsTemplate(VideoDriver* driver) : Base(driver) {}

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
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreatePointImplementation(VERTEX_1)
#undef VERTEX_1
}
