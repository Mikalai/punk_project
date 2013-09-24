#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

#include "../../system/object.h"
#include "../../system/aop/aop.h"
#include "../../system/serializable.h"
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
    class PUNK_ENGINE_API Animation : public System::Object
	{
		AnimationTrack<Math::vec3> m_pos_track;
		AnimationTrack<Math::quat> m_rot_track;
        System::string m_name;
	public:
		Animation();
		Animation(Utility::AnimationDesc& desc);
		void AddPositionKey(int frame, Math::vec3& position);
		void AddRotationKey(int frame, Math::quat& rotation);
		
		Math::vec3& GetOrCreatePositionKey(int frame);
		Math::quat& GetOrCreateRotationKey(int frame);

		const Math::vec3 GetPosition(float frame) const;
		const Math::quat GetRotation(float frame) const;

		void SetPositionTrack(const AnimationTrack<Math::vec3>& track) { m_pos_track = track; }
		void SetRotationTrack(const AnimationTrack<Math::quat>& track) { m_rot_track = track; }

        const System::string& GetName() const;
        void SetName(const System::string& value);

        friend void SaveAnimation(System::Buffer* buffer, const Object* o);
        friend void LoadAnimation(System::Buffer* buffer, Object* o);
	};

    PUNK_ENGINE_API void SaveAnimation(System::Buffer* buffer, const System::Object* o);
    PUNK_ENGINE_API void LoadAnimation(System::Buffer* buffer, System::Object* o);
}

#endif
