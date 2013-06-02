#ifndef _H_PUNK_TRIANGLES
#define _H_PUNK_TRIANGLES

#include "../renderable.h"
#include "../vertex.h"

#define CreateTrianglesInterface(VertexType)\
template<>\
class PUNK_ENGINE_API Triangles<VertexType> : public Renderable {\
public:\
    Triangles<VertexType>(VideoDriver* driver);\
    virtual ~Triangles<VertexType>();\
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

    template<typename VertexType>class PUNK_ENGINE_API Triangles;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1
}

#endif	//	_H_PUNK_OPENGL_TRIANGLES
