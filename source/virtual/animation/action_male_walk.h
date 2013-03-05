#ifndef _H_PUNK_VIRTUAL_ANIMATION_MALE_WALK
#define _H_PUNK_VIRTUAL_ANIMATION_MALE_WALK

#include "action.h"

namespace Virtual
{
	class PUNK_ENGINE ActionMaleWalk sealed : public Action
	{
	public:
		static ActionMaleWalk* CreateFromFile(const System::string& path);
		static ActionMaleWalk* CreateFromStream(std::istream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_ANIMATION_MALE_WALK