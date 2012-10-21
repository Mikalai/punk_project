#include "object_animation.h"

namespace Virtual
{

	ObjectAnimation::~ObjectAnimation()
	{
	}

	bool ObjectAnimation::Save(std::ostream& stream)
	{
		if (!Animation::Save(stream))
			return false;
		return false;
	}

	bool ObjectAnimation::Load(std::istream& stream)
	{
		if (!Animation::Load(stream))
			return false;
		return false;
	}
}
