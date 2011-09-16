#ifndef _H_UTIL_PUNK_SKINNED_MESH
#define _H_UTIL_PUNK_SKINNED_MESH

#include "../config.h"
#include "static_mesh.h"
#include "vertex.h"

namespace Utility
{
	class LIB_UTILITY SkinnedMesh : public StaticMesh
	{
		friend class Model;
	};
}

#endif