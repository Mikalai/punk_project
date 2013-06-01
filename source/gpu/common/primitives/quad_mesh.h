#ifndef _H_PUNK_OPENGL_QUAD
#define _H_PUNK_OPENGL_QUAD

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{
#ifdef USE_OPENGL
	using QuadObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

	class QuadObject final : public QuadObjectBase
	{
		using Base = QuadObjectBase;
	public:
		QuadObject(VideoDriver* driver);
		void Cook(float width, float height);

	};
}

#endif
