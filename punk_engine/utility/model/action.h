#ifndef _H_PUNK_UTILITY_ACTION
#define _H_PUNK_UTILITY_ACTION

#include "../../system/string.h"
#include "skeleton_animation.h"

namespace Utility
{
	typedef int FrameID;
	struct Action
	{
		System::string m_name;
		FrameID m_start_frame;
		FrameID m_end_frame;
		int m_key_count;
		SkeletonAnimation m_pose;
	};
}

#endif