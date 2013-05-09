#ifndef _H_PUNK_OPENGL_SPHERE_MESH
#define _H_PUNK_OPENGL_SPHERE_MESH

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif

namespace GPU
{
#ifdef USE_OPENGL
	using SphereObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::LINE_LOOP,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Tangent,
	VertexComponent::Bitangent,
	VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

	class PUNK_ENGINE SphereObject : public SphereObjectBase
	{
		using Base = SphereObjectBase;

	public:
		SphereObject(VideoDriver* driver);
		void Cook(float radius);
	};
}

#endif	//	_H_PUNK_OPENGL_SPHERE_MESH
