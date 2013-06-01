#ifndef _H_PUNK_VIRTUAL_ARMATURE_DESC
#define _H_PUNK_VIRTUAL_ARMATURE_DESC

#include <vector>
#include "../../config.h"
#include "../../string/string.h"

namespace Utility
{
	class BoneDesc;

	class PUNK_ENGINE_PUBLIC ArmatureDesc
	{
	public:
		System::string m_name;
		std::vector<BoneDesc*> m_bones;

		~ArmatureDesc();

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif