#ifndef _H_PUNK_OPENGL_TRIANGLES
#define _H_PUNK_OPENGL_TRIANGLES

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using TrianglesBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, VertexType>;
#else
#endif

	template<typename VertexType>
	class PUNK_ENGINE_PUBLIC Triangles: public TrianglesBase<VertexType>
	{
		using Base = TrianglesBase<VertexType>;

	public:

		Triangles(VideoDriver* driver) : Base(driver) {}

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

#endif	//	_H_PUNK_OPENGL_TRIANGLES
