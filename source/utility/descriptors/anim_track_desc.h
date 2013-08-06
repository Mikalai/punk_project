#ifndef _H_PUNK_VIRTUAL_ANIM_TRACK
#define _H_PUNK_VIRTUAL_ANIM_TRACK

#include "../../math/vec3.h"
#include "../../math/quat.h"
#include "../../virtual/animation/animation_track.h"

namespace Utility
{
	class AnimationTrackDesc
	{
		bool m_is_position_track;
		bool m_is_rotation_track;

		Virtual::AnimationTrack<Math::vec3> m_position_track;
		Virtual::AnimationTrack<Math::quat> m_rotation_track;
	};
}

#endif