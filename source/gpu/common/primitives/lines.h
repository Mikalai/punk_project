#ifndef _H_PUNK_LINES
#define _H_PUNK_LINES

#include "../renderable.h"
#include "../vertex.h"

#define CreateLineInterface(VertexType)\
template<>\
class PUNK_ENGINE_API Lines<VertexType> : public Renderable {\
public:\
    Lines<VertexType>(VideoDriver* driver);\
    virtual ~Lines<VertexType>();\
    void Cook(const std::vector<VertexType>& value);\
    virtual void Bind(int64_t) override;\
    virtual void Unbind() override;\
    virtual void Render() override;\
private:\
    Renderable* impl;\
}

namespace Gpu
{
    class VideoDriver;

    template<class VertexType> class Lines;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1
}

#endif	//	_H_PUNK_LINES
