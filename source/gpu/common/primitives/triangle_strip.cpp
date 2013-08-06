#ifndef _H_PUNK_OPENGL_TRIANGLE_STRIP
#define _H_PUNK_OPENGL_TRIANGLE_STRIP

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

#define CreateTriangleStripsImplementation(VertexType) \
    TriangleStrip<VertexType>::TriangleStrip(VideoDriver* driver) \
    : impl(new TriangleStripTemplate<VertexType>(driver)) {} \
    TriangleStrip<VertexType>::~TriangleStrip<VertexType>() { \
    delete impl; impl = nullptr; }\
    void  TriangleStrip<VertexType>::Cook(const std::vector<VertexType>& value) {\
    dynamic_cast<TriangleStripTemplate<VertexType>*>(impl)->Cook(value); }\
    void  TriangleStrip<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  TriangleStrip<VertexType>::Unbind() { \
impl->Unbind(); }\
void  TriangleStrip<VertexType>::Render() {\
    impl->Render();}

namespace Gpu
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using TriangleStripBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_STRIP, VertexType>;
#else
#endif

	template<typename VertexType>
    class PUNK_ENGINE_API TriangleStripTemplate: public TriangleStripBase<VertexType>
	{
		using Base = TriangleStripBase<VertexType>;

	public:

        TriangleStripTemplate(VideoDriver* driver) : Base(driver) {}

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

    CreateTriangleStripsImplementation(Vertex<VertexComponent::Position>)
}

#endif	//	_H_PUNK_OPENGL_TRIANGLE_STRIP
