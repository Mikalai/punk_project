#ifndef _H_UTIL_PUNK_SKINNED_MESH
#define _H_UTIL_PUNK_SKINNED_MESH

#include "../config.h"
#include "static_mesh.h"
#include "../utility/model/vertex.h"

namespace Utility
{
	class PUNK_ENGINE SkinnedMesh : public StaticMesh
	{
		friend class Model;
	};
}

#endif