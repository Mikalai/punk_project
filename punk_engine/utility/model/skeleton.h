#ifndef _H_PUNK_SKELETON
#define _H_PUNK_SKELETON

#include "bone.h"

namespace Utility
{
	typedef std::map<BoneName, Bone> Skeleton;
	typedef std::map<unsigned, Bone> SkeletonID;
}

#endif