#ifndef _H_PUNK_VIRTUAL_MESH_DESCRIPTOR
#define _H_PUNK_VIRTUAL_MESH_DESCRIPTOR

#include <vector>
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/vec2.h"
#include "../../math/bounding_box.h"
#include "../../virtual/skinning/types.h"
#include "../../utility/model/vertex_bone_weight.h"

namespace Utility
{

	typedef int FaceIndex;
	typedef std::vector<Math::vec3> Vertices;
	typedef std::vector<Math::vec3> Normals;	
	typedef std::vector<Math::ivec3> Faces;
	typedef Math::BoundingBox BoundingBox;		
	typedef std::map<System::string, std::vector<Math::Vector4<Math::vec2>>> TextureMeshes;

	class PUNK_ENGINE_PUBLIC MeshDesc
	{		
	public:
		Vertices m_vertices;
		Normals m_normals;
		Faces m_faces;
		Virtual::VertexBoneWeights m_bone_weights;
		TextureMeshes m_tex_coords;
		std::vector<System::string> m_material_ref;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		std::wostream& out_formatted(std::wostream& stream);
	};}

#endif	//	_H_PUNK_VIRTUAL_MESH_DESCRIPTOR