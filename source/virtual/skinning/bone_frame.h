#ifndef _H_PUNK_BONE_FRAME
#define _H_PUNK_BONE_FRAME

#include <map>
#include "../../math/quat.h"
#include "../../math/vec3.h"

namespace Utility
{
	class BoneFrame
	{
	public:
		Math::quat m_rotation;
		Math::vec3 m_position;		
	};
	typedef int FrameID;
	typedef std::map<FrameID, BoneFrame> FramesCollection;
}

#endif
