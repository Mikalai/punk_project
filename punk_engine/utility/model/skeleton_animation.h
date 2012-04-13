#ifndef _H_PUNK_UTILITY_SKELETON_ANIMATION
#define _H_PUNK_UTILITY_SKELETON_ANIMATION

namespace Utility
{
	struct BoneAnimation
	{
		System::string m_bone_name;
		FramesCollection m_frames;
	};
	typedef std::map<BoneName, BoneAnimation> SkeletonAnimation;
}

#endif