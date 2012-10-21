#include "../../system/logger.h"
#include "armature_desc.h"
#include "bone_desc.h"

namespace Utility
{
	std::wostream& ArmatureDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		for (auto bone : m_bones)
			bone->out_formatted(stream) << std::endl;

		stream << Tab::Dec() << typeid(*this).name();
		return stream;		
	}

	ArmatureDesc::~ArmatureDesc()
	{
		for (auto bone : m_bones)
			delete bone;
	}
}