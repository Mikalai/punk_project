#ifndef _H_PUNK_OPENGL_TRIANGLE_FAN
#define _H_PUNK_OPENGL_TRIANGLE_FAN

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using TriangleFanBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_FAN, VertexType>;
#else
#endif	//	USE_OPENGL

	template<typename VertexType>
	class PUNK_ENGINE TriangleFan: public TriangleFanBase<VertexType>
	{
		using Base = TriangleFanBase<VertexType>;
	public:

		TriangleFan(VideoDriver* driver) : Base(driver) {}

		void Cook(const std::vector<Vertex<VertexType>>& value)
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

#endif	//	_H_PUNK_OPENGL_TRIANGLE_FAN
