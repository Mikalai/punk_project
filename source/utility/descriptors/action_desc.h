#ifndef _H_PUNK_VIRTUAL_ACTION_DESC
#define _H_PUNK_VIRTUAL_ACTION_DESC

#include "../../config.h"
#include "../../virtual/animation/action.h"
#include "../../string/string.h"

namespace Utility
{
	class AnimationDesc;

	class PUNK_ENGINE_API ActionDesc
	{
	public:
		System::string m_name;
		int m_start;
		int m_end;
		std::vector<AnimationDesc*> m_animation;

		~ActionDesc();

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_ACTION_DESC