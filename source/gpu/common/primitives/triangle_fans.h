#ifndef _H_PUNK_TRIANGLE_FAN
#define _H_PUNK_TRIANGLE_FAN

#include "../renderable.h"
#include "../vertex.h"

#define CreateTriangleFansInterface(VertexType)\
template<>\
class PUNK_ENGINE_API TriangleFan<VertexType> : public Renderable {\
public:\
    TriangleFan<VertexType>(VideoDriver* driver);\
    virtual ~TriangleFan<VertexType>();\
    void Cook(const std::vector<VertexType>& value);\
    virtual void Bind(int64_t) override;\
    virtual void Unbind() override;\
    virtual void Render() override;\
private:\
    Renderable* impl;\
}

namespace GPU
{
    class VideoDriver;
    template<typename VertexType> class TriangleFan;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1
}

#endif	//	_H_PUNK_TRIANGLE_FAN
