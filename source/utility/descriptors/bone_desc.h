#ifndef _H_PUNK_VIRTUAL_BONE_DESC
#define _H_PUNK_VIRTUAL_BONE_DESC

#include "../../config.h"
#include "../../string/string.h"
#include "../../math/mat4.h"

namespace Utility
{
	class PUNK_ENGINE BoneDesc
	{
	public:
		System::string m_name;
		System::string m_parent;
		float m_length;
		Math::mat4 m_local;

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_BONE_DESC