#include "animation_mixer.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(AnimationMixer, "Virtual.AnimationMixer", PUNK_ANIMATION_MIXER, SaveAnimationMixer, LoadAnimationMixer, &System::Object::Info.Type);

    AnimationMixer::AnimationMixer()
    {
        Info.Add(this);
    }

	AnimationMixer::~AnimationMixer()
    {
        Info.Remove(this);
    }

    void SaveAnimationMixer(System::Buffer* buffer, const System::Object* anim)
    {
        System::SaveObject(buffer, anim);
    }

    void LoadAnimationMixer(System::Buffer* buffer, System::Object* anim)
    {
        System::LoadObject(buffer, anim);
    }
}
