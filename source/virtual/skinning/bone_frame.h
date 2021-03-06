#ifndef _H_PUNK_BONE_FRAME
#define _H_PUNK_BONE_FRAME

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