#ifndef _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
#define _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace Virtual { class SkinGeometry; }
namespace Virtual { class Armature; }

namespace Math { class vec4; }

namespace GPU
{
#ifdef USE_OPENGL
	using SkinMeshBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Tangent,
	VertexComponent::Bitangent,
	VertexComponent::Texture0,
	VertexComponent::BoneID,
	VertexComponent::BoneWeight>>;
#else
#endif

	class PUNK_ENGINE_PUBLIC SkinMesh : public SkinMeshBase
	{
		using Base = SkinMeshBase;

	public:
		SkinMesh(VideoDriver* driver);
		bool Cook(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature);
	};
}

#endif	//	_H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
