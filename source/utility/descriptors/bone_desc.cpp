#include "bone_desc.h"
#include "../../system/logger.h"

namespace Utility
{
	std::wostream& BoneDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		stream << Tab() << "Parent: " << m_parent.Data() << std::endl;
		stream << Tab() << "Length: " << m_length << std::endl;
		stream << Tab() << "Local matrix: \n" << m_local << std::endl;
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}