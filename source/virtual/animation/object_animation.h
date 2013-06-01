#ifndef _H_PUNK_VIRTUAL_OBJECT_ANIMATION
#define _H_PUNK_VIRTUAL_OBJECT_ANIMATION

#include "animation.h"

namespace Virtual
{
	class ObjectAnimation : public Animation
	{
	public:
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~ObjectAnimation();
	};
}

#endif	//	_H_PUNK_VIRTUAL_OBJECT_ANIMATION