#ifndef _H_PUNK_OPENGL_LINES
#define _H_PUNK_OPENGL_LINES

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using LinesBase = OpenGL::VertexArrayObject2<PrimitiveType::LINES, VertexType>;
#else
#endif	//	USE_OPENGL

	template<typename VertexType>
	class PUNK_ENGINE_PUBLIC Lines : public LinesBase<VertexType>
	{
		using Base = LinesBase<VertexType>;

	public:

		Lines(VideoDriver* driver) : Base(driver) {}

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

#endif	//	_H_PUNK_OPENGL_LINES
