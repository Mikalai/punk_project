#ifndef _H_PUNK_UTILITY_ANIMATION_MixER
#define _H_PUNK_UTILITY_ANIMATION_MixER

#include "../../config.h"
#include "../../system/object.h"

namespace System { class string; }

namespace Virtual
{
	class PUNK_ENGINE_API AnimationMixer : public System::Object
	{
	public:
        AnimationMixer();
        AnimationMixer(const AnimationMixer&) = delete;
        AnimationMixer& operator = (const AnimationMixer&) = delete;
		virtual ~AnimationMixer();

        virtual void SetTrackTime(float /*time*/) {}
        virtual float GetTrackTime() const {return 0;}
        virtual void SetLooping(size_t, bool) {}

        PUNK_OBJECT(AnimationMixer)

        friend void SaveAnimationMixer(System::Buffer* buffer, const Object* anim);
        friend void LoadAnimationMixer(System::Buffer* buffer, Object* anim);
	};

    PUNK_ENGINE_API void SaveAnimationMixer(System::Buffer* buffer, const System::Object* anim);
    PUNK_ENGINE_API void LoadAnimationMixer(System::Buffer* buffer, System::Object* anim);
}

#endif
