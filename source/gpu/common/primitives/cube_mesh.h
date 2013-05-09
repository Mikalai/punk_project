#ifndef _H_PUNK_OPENGL_CUBE_MESH
#define _H_PUNK_OPENGL_CUBE_MESH

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{
#ifdef USE_OPENGL
	using CubeObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Tangent,
	VertexComponent::Bitangent,
	VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

	class CubeObject : public CubeObjectBase
	{
		using Base = CubeObjectBase;
	public:
		CubeObject(GPU::VideoDriver* driver);
		void Cook(float width, float height, float depth);

	};
}

#endif	//	_H_PUNK_OPENGL_CUBE_MESH
