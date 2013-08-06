#include "animation_mixer.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(AnimationMixer, "Virtual.AnimationMixer", PUNK_ANIMATION_MIXER, &System::Object::Info.Type);

    AnimationMixer::AnimationMixer()
    {
        Info.Add(this);
    }

	AnimationMixer::~AnimationMixer()
    {
        Info.Remove(this);
    }
}
