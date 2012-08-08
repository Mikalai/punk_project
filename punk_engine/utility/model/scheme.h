#ifndef _H_PUNK_UTILITY_MODEL
#define _H_PUNK_UTILITY_MODEL

#include "../config.h"
#include "../../math/math.h"
#include "../../system/system.h"
#include "../../images/images.h"
#include "../../system/string.h"
#include <map>
#include <vector>
#include "material.h"
#include "armature.h"

namespace Utility
{
	class StaticMesh;
	class SkinnedMesh;
	class SkinAnimation;

	typedef std::map<System::string, Material> MaterialCollection;

	class LIB_UTILITY RawScene
	{	
		MaterialCollection m_materials;
	public:
		void OpenFile(const System::string& filename);
		StaticMesh* CookStaticMesh(const System::string& name);
		SkinnedMesh* CookSkinnedMesh(const System::string& name);
		SkinAnimation* CookSkinAnimation(const System::string& mesh_name, unsigned anim_id);		

		Material GetMaterial(const System::string& name) const;
		Material GetMaterial(unsigned index) const;

	private:		
	};
}


#endif