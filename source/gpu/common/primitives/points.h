#ifndef _H_PUNK_OPENGL_POINTS_VAO
#define _H_PUNK_OPENGL_POINTS_VAO

#include <vector>
#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{
#ifdef USE_OPENGL
	template<typename VertexType>
	using PointsBase = OpenGL::VertexArrayObject2<PrimitiveType::POINTS, VertexType>;
#else
#endif

	template<typename VertexType>
	class PUNK_ENGINE_PUBLIC Points : public PointsBase<VertexType>
	{
		using Base = PointsBase<VertexType>;

	public:

		Points(VideoDriver* driver) : Base(driver) {}

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

#endif	//	_H_PUNK_OPENGL_POINTS_VAO
