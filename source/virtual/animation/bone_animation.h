#ifndef _H_PUNK_VIRTUAL_BONE_ANIMATION
#define _H_PUNK_VIRTUAL_BONE_ANIMATION

#include "animation.h"

namespace Virtual
{
    class BoneAnimation : public Animation, public System::Aspect<Animation*, System::string>
	{
	public:
		BoneAnimation();
		virtual ~BoneAnimation();
	};
}

#endif	//	_H_PUNK_VIRTUAL_BONE_ANIMATION
