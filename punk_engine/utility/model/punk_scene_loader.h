#ifndef _H_PUNK_SCENE_LOADER
#define _H_PUNK_SCENE_LOADER

#include "../config.h"
#include <vector>

namespace System
{
	class string;
}

namespace Math
{
	class OctTree;
	template<class T> class Vector3;
}

namespace Utility
{
	class LIB_UTILITY Scene
	{
		struct SceneImpl;
		std::auto_ptr<SceneImpl> impl_scene;
	public:
		Scene();
		Scene(const Scene& scene);
		Scene& operator = (const Scene& scene);
		~Scene();

		void Load(const System::string& filename);
		Math::OctTree& GetOctTree();
		bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, std::vector<Math::Vector3<float>>& points);
	};


};

#endif