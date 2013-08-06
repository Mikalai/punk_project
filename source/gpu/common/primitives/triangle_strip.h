#ifndef _H_PUNK_TRIANGLE_STRIPS
#define _H_PUNK_TRIANGLE_STRIPS

#include "../renderable.h"

#define CreateTriangleStripsInterface(VertexType)\
template<>\
class PUNK_ENGINE_API TriangleStrip<VertexType> : public Renderable {\
public:\
    TriangleStrip<VertexType>(VideoDriver* driver);\
    virtual ~TriangleStrip<VertexType>();\
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

    template<typename VertexType> class TriangleStrip;

    CreateTriangleStripsInterface(Vertex<VertexComponent::Position>);
}

#endif	//	_H_PUNK_TRIANGLE_STRIPS
