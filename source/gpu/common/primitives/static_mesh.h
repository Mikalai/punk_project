#ifndef _H_PUNK_OPENGL_MODULE_STATIC_OBJECT
#define _H_PUNK_OPENGL_MODULE_STATIC_OBJECT

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace Virtual { class StaticGeometry; }

namespace GPU
{
#ifdef USE_OPENGL
	using StaticMeshBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Tangent,
	VertexComponent::Bitangent,
	VertexComponent::Texture0>>;
#else
#endif

	class PUNK_ENGINE StaticMesh : public StaticMeshBase
	{
		using Base = StaticMeshBase;

	public:

		StaticMesh(VideoDriver* driver);

		bool Cook(Virtual::StaticGeometry* desc);
	};
}

#endif
