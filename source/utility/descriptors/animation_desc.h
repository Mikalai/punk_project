#ifndef _H_PUNK_VIRTUAL_ANIMATION_DESC
#define _H_PUNK_VIRTUAL_ANIMATION_DESC

#include "../../math/vec3.h"
#include "../../math/quat.h"
#include "../../virtual/animation/animation_track.h"
#include "../../string/string.h"

namespace Utility
{
	class AnimationDesc
	{
	public:
		bool m_is_bone_anim;
		System::string m_bone_name;
		Virtual::AnimationTrack<Math::vec3> m_pos_track;
		Virtual::AnimationTrack<Math::quat> m_rot_track;

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_ANIMATION_DESC