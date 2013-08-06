#ifndef _H_PUNK_VIRTUAL_HUMAN_MALE_ARMATURE
#define _H_PUNK_VIRTUAL_HUMAN_MALE_ARMATURE

#include "human_armature.h"

namespace Virtual
{
	class PUNK_ENGINE_API HumanMaleArmature final : public HumanArmature
	{
	public:
        HumanMaleArmature();
        HumanMaleArmature(const HumanMaleArmature&) = delete;
        HumanArmaturePart& operator = (const HumanMaleArmature&);
        virtual ~HumanMaleArmature();

    private:
        PUNK_OBJECT(HumanMaleArmature)
	};
};

#endif	//	_H_PUNK_VIRTUAL_HUMAN_MALE_ARMATURE
