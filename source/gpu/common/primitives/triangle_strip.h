#ifndef _H_PUNK_OPENGL_TRIANGLE_STRIP
#define _H_PUNK_OPENGL_TRIANGLE_STRIP

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using TriangleStripBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_STRIP, VertexType>;
#else
#endif

	template<typename VertexType>
	class PUNK_ENGINE_PUBLIC TriangleStrip: public TriangleStripBase<VertexType>
	{
		using Base = TriangleStripBase<VertexType>;

	public:

		TriangleStrip(VideoDriver* driver) : Base(driver) {}

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
}

#endif	//	_H_PUNK_OPENGL_TRIANGLE_STRIP
