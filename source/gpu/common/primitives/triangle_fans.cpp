#ifndef _H_PUNK_OPENGL_TRIANGLE_FAN
#define _H_PUNK_OPENGL_TRIANGLE_FAN

#include "triangle_fans.h"

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

#define CreateTriangleFansImplementation(VertexType) \
    TriangleFan<VertexType>::TriangleFan(VideoDriver* driver) \
    : impl(new TriangleFanTemplate<VertexType>(driver)) {} \
    TriangleFan<VertexType>::~TriangleFan() { \
    delete impl; impl = nullptr; }\
    void  TriangleFan<VertexType>::Cook(const std::vector<VertexType>& value) {\
    dynamic_cast<TriangleFanTemplate<VertexType>*>(impl)->Cook(value); }\
    void  TriangleFan<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  TriangleFan<VertexType>::Unbind() { \
impl->Unbind(); }\
void  TriangleFan<VertexType>::Render() {\
    impl->Render();}

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using TriangleFanBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_FAN, VertexType>;
#else
#endif	//	USE_OPENGL

	template<typename VertexType>
    class PUNK_ENGINE_API TriangleFanTemplate: public TriangleFanBase<VertexType>
	{
		using Base = TriangleFanBase<VertexType>;
	public:

        TriangleFanTemplate(VideoDriver* driver) : Base(driver) {}

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
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTriangleFansImplementation(VERTEX_1)
#undef VERTEX_1
}

#endif	//	_H_PUNK_OPENGL_TRIANGLE_FAN
