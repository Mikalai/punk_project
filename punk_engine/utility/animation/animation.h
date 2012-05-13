#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

#include "../config.h"
#include "animation_track.h"
#include "../../math/vec3.h"
#include "../../math/quat.h"

namespace Utility
{
	class LIB_UTILITY Animation
	{
		bool m_is_enabled;		
		AnimationTrack<Math::Vector3<float>> m_pos_track;
		AnimationTrack<Math::Quaternion<float>> m_rot_track;
	public:
		Animation();
		void AddPositionKey(int frame, Math::Vector3<float>& position);
		void AddRotationKey(int frame, Math::Quaternion<float>& rotation);
		
		Math::Vector3<float>& GetOrCreatePositionKey(int frame);
		Math::Quaternion<float>& GetOrCreateRotationKey(int frame);

		const Math::Vector3<float> GetPosition(int frame);
		const Math::Quaternion<float> GetRotation(int frame);

		void Enable(bool flag);
		bool IsEnabled() const;

		void SetLooping(bool flag);
		bool IsLooping() const;
	};
}

#endif