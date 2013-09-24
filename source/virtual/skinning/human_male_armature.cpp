#include "human_male_armature.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(HumanMaleArmature, "Virtual.HumanMaleArmature", PUNK_HUMAN_MALE_ARMATURE, SaveHumanMaleArmature, LoadHumanMaleArmature, &HumanArmature::Info.Type);

    HumanMaleArmature::HumanMaleArmature()
    {
        Info.Add(this);
    }

    HumanMaleArmature::~HumanMaleArmature()
    {
        Info.Remove(this);
    }

    void SaveHumanMaleArmature(System::Buffer *buffer, const System::Object *o)
    {
        SaveHumanArmature(buffer, o);
    }

    void LoadHumanMaleArmature(System::Buffer *buffer, System::Object *o)
    {
        LoadHumanArmature(buffer, o);
    }
}
