#include "action_desc.h"
#include "animation_desc.h"
#include "../../system/logger.h"

namespace Utility
{
	ActionDesc::~ActionDesc()
	{
		for (auto anim : m_animation)
			delete anim;
	}

	std::wostream& ActionDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		stream << Tab() << "Start: " << m_start << std::endl;
		stream << Tab() << "End: " << m_end << std::endl;
		stream << Tab() << "Animations: " << std::endl;
		Tab::Inc();
		for (auto anim : m_animation)
		{
			anim->out_formatted(stream) << std::endl;
		}
		Tab::Dec();
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}