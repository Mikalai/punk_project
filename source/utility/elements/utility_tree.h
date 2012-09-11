#ifndef _H_PUNK_UTILITY_TREE
#define _H_PUNK_UTILITY_TREE

#include "../utility_lod.h"
#include "../model/punk_scene_loader.h"

namespace Utility
{
	class PUNK_ENGINE Tree
	{
		LodContainer m_trunks;
		LodContainer m_top_leaves;
		LodContainer m_bottom_leaves;
	public:
		void MakeFromScene(Scene& scene);

		LodContainer& GetTrunkLods() { return m_trunks; }
		LodContainer& GetTopLeavesLods() { return m_top_leaves; }
		LodContainer& GetBottomLods() { return m_bottom_leaves; }

		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};
}

#endif