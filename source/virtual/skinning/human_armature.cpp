#include "human_armature.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(HumanArmature, "Virtual.HumanArmature", PUNK_HUMAN_ARMATURE, SaveHumanArmature, LoadHumanArmature, &Armature::Info.Type);

	struct HumanArmaturePartAdapter
	{
		HumanArmaturePart key;
		const wchar_t* value;
	};

	static const HumanArmaturePartAdapter HumanPart[] = {
		{ HUMAN_ROOT, L"root" },
		{ HUMAN_HEAD, L"head" },
		{ HUMAN_NECK, L"neck" },
		{ HUMAN_COLLAR_LEFT, L"collar.l" },
		{ HUMAN_COLLAR_RIGHT, L"collar.r" },
		{ HUMAN_UPPER_ARM_LEFT, L"upperarm.l" },
		{ HUMAN_UPPER_ARM_RIGHT, L"upperarm.r" },
		{ HUMAN_LOWER_ARM_LEFT, L"lowerarm.l" },
		{ HUMAN_LOWER_ARM_RIGHT, L"lowerarm.r" },
		{ HUMAN_PALM_LEFT, L"palm.l" },
		{ HUMAN_PALM_RIGHT, L"palm.r" },
		{ HUMAN_BIG_FINGER_A_LEFT, L"ta.l" },
		{ HUMAN_BIG_FINGER_A_RIGHT, L"ta.r" },
		{ HUMAN_BIG_FINGER_B_LEFT, L"tb.l" },
		{ HUMAN_BIG_FINGER_B_RIGHT, L"tb.r" },
		{ HUMAN_BIG_FINGER_C_LEFT, L"tc.l" },
		{ HUMAN_BIG_FINGER_C_RIGHT, L"tc.r" },
		{ HUMAN_FINGER_1_A_LEFT, L"f1a.l" },
		{ HUMAN_FINGER_1_A_RIGHT, L"f1a.r" },
		{ HUMAN_FINGER_1_B_LEFT, L"f1b.l" },
		{ HUMAN_FINGER_1_B_RIGHT, L"f1b.r" },
		{ HUMAN_FINGER_1_C_LEFT, L"f1c.l" },
		{ HUMAN_FINGER_1_C_RIGHT, L"f1c.r" },
		{ HUMAN_FINGER_2_A_LEFT, L"f2a.l" },
		{ HUMAN_FINGER_2_A_RIGHT, L"f2a.r" },
		{ HUMAN_FINGER_2_B_LEFT, L"f2b.l" },
		{ HUMAN_FINGER_2_B_RIGHT, L"f2b.r" },
		{ HUMAN_FINGER_2_C_LEFT, L"f2c.l" },
		{ HUMAN_FINGER_2_C_RIGHT, L"f2c.r" },
		{ HUMAN_FINGER_3_A_LEFT, L"f3a.l" },
		{ HUMAN_FINGER_3_A_RIGHT, L"f3a.r" },
		{ HUMAN_FINGER_3_B_LEFT, L"f3b.l" },
		{ HUMAN_FINGER_3_B_RIGHT, L"f3b.r" },
		{ HUMAN_FINGER_3_C_LEFT, L"f3c.l" },
		{ HUMAN_FINGER_3_C_RIGHT, L"f3c.r" },
		{ HUMAN_FINGER_4_A_LEFT, L"f4a.l" },
		{ HUMAN_FINGER_4_A_RIGHT, L"f4a.r" },
		{ HUMAN_FINGER_4_B_LEFT, L"f4b.l" },
		{ HUMAN_FINGER_4_B_RIGHT, L"f4b.r" },
		{ HUMAN_FINGER_4_C_LEFT, L"f4c.l" },
		{ HUMAN_FINGER_4_C_RIGHT, L"f4c.r" },		
		{ HUMAN_CHEST, L"chest" },
		{ HUMAN_STOMACH, L"stomach" },
		{ HUMAN_BASE, L"base" },
		{ HUMAN_PELVIS, L"pelvis" },
		{ HUMAN_THIGH_LEFT, L"thigh.l" },
		{ HUMAN_THIGH_RIGHT, L"thigh.r" },
		{ HUMAN_LOWER_LEG_LEFT, L"lowerleg.l" },
		{ HUMAN_LOWER_LEG_RIGHT, L"lowerleg.r" },
		{ HUMAN_FOOT_LEFT, L"foot.l" },
		{ HUMAN_FOOT_RIGHT, L"foot.r" },
		{ HUMAN_TOE_LEFT, L"toe.l" },
		{ HUMAN_TOE_RIGHT, L"toe.r" } };

	void HumanArmature::UpdateHierarchy()
	{
		Armature::UpdateHierarchy();

		for (int i = HUMAN_BEGIN; i != HUMAN_END; ++i)
		{
			m_bone_index[HumanPart[i].key] = GetBoneIndex(HumanPart[i].value);
		}
	}

    HumanArmature::HumanArmature()
    {
        Info.Add(this);
    }

    HumanArmature::~HumanArmature()
    {
        Info.Remove(this);
    }

    void SaveHumanArmature(System::Buffer *buffer, const System::Object *o)
    {
        SaveArmature(buffer, o);
    }

    void LoadHumanArmature(System::Buffer *buffer, System::Object *o)
    {
        LoadArmature(buffer, o);
        HumanArmature* a = Cast<HumanArmature*>(o);
        a->UpdateHierarchy();
    }
}
