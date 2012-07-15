#ifndef _H_PUNK_SCENE_LOADER
#define _H_PUNK_SCENE_LOADER

#include "../config.h"
#include <vector>
#include "intersection.h"
#include "armature.h"

namespace Math
{
	class OctTree;
	template<class T> class Vector3;
}

namespace System
{
	class string;
}

namespace Utility
{
	class StaticMesh;

	class LIB_UTILITY Scene
	{
		struct SceneImpl;
		std::auto_ptr<SceneImpl> impl_scene;
	public:
		Scene();
		Scene(const Scene& scene);
		Scene& operator = (const Scene& scene);
		~Scene();

		unsigned GetObjectsCount() const;
		const System::string& GetObjectName(int index) const;

		void Load(const System::string& filename);
		//Math::OctTree& GetOctTree();
		bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res);
		StaticMesh* CookStaticMesh(const System::string& name) const;
		StaticMesh* CookSkinnedMesh(const System::string& name) const;
		Armature* GetArmature(const System::string& name);
		int GetArmatureCount() const;
		const System::string& GetArmatureName(int index) const;

		void PrintDebug();
	};


};

#endif