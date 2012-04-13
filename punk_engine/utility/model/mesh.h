#ifndef _H_PUNK_UTILITY_MESH
#define _H_PUNK_UTILITY_MESH

#include "../../math/vec3.h"

namespace Utility
{
	typedef int VertexIndex;
	typedef int FaceIndex;
	typedef std::vector<Math::vec3> Vertices;
	typedef std::vector<Math::vec3> Normals;	
	typedef std::vector<Math::ivec3> Faces;
	typedef Math::BoundingBox BoundingBox;		
}

#endif