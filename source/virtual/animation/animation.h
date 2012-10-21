#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

#include "../../system/object.h"

#include "../../config.h"
#include "animation_track.h"
#include "../../math/vec3.h"
#include "../../math/quat.h"

namespace Utility
{
	class AnimationDesc;
}

namespace Virtual
{
	enum AnimationType { NONE, OBJECT, BONE };

	class PUNK_ENGINE Animation : public System::Object
	{
		AnimationTrack<Math::Vector3<float>> m_pos_track;
		AnimationTrack<Math::Quaternion<float>> m_rot_track;
		AnimationType m_animation_type;
	public:
		Animation();
		Animation(Utility::AnimationDesc& desc);
		void AddPositionKey(int frame, Math::Vector3<float>& position);
		void AddRotationKey(int frame, Math::Quaternion<float>& rotation);
		
		Math::Vector3<float>& GetOrCreatePositionKey(int frame);
		Math::Quaternion<float>& GetOrCreateRotationKey(int frame);

		const Math::Vector3<float> GetPosition(float frame) const;
		const Math::Quaternion<float> GetRotation(float frame) const;

		AnimationType GetAnimationType() const { return m_animation_type; }

		virtual bool Save(std::ostream& stream);
		virtual bool Load(std::istream& stream);
	};
}

#endif