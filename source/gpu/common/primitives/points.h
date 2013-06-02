#ifndef _H_PUNK_OPENGL_POINTS_VAO
#define _H_PUNK_OPENGL_POINTS_VAO

#include "../renderable.h"
#include "../vertex.h"

#define CreatePointInterface(VertexType) \
template<>\
class PUNK_ENGINE_API Points<VertexType> : public Renderable {\
public:\
    Points<VertexType>(VideoDriver* driver);\
    virtual ~Points<VertexType>();\
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

    template<typename VertexType> class Points;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreatePointInterface(VERTEX_1);
#undef VERTEX_1

}

#endif	//	_H_PUNK_OPENGL_POINTS_VAO
