#ifndef _H_PUNK_UTILITY_LOD
#define _H_PUNK_UTILITY_LOD

#include "../config.h"
#include <vector>
//#include "static_mesh.h"
#include <iosfwd>

namespace Utility
{
	class StaticMesh;

	class PUNK_ENGINE LodContainer
	{
		//	meshes go from very detailed to completely undetailed
		std::vector<StaticMesh*> m_meshes;
	public:
		//	meshes should be pushed in decreasing order
		void PushLod(StaticMesh* lod);
		StaticMesh* GetLod(int level);

		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};
}

#endif