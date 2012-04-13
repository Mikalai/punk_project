#ifndef _H_PUNK_SKELETON
#define _H_PUNK_SKELETON

#include "bone.h"
#include <memory>
namespace System
{
	class string;
}

namespace Utility
{
	typedef std::map<BoneName, std::shared_ptr<Bone>> BonesCollection;
	typedef std::map<unsigned, Bone> SkeletonID;
	
	struct Armature
	{
		System::string m_name;
		BonesCollection m_bones;
	};

	typedef std::vector<std::shared_ptr<Armature>> ArmatureCollection;
}

#endif