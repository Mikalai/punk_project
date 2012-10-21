#include "camera_desc.h"
#include "../../system/logger.h"

namespace Utility
{
	std::wostream& CameraDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		stream << Tab() << "Type: " << m_type.Data() << std::endl;
		stream << Tab() << "FOV: " << m_fov << std::endl;
		stream << Tab() << "Near: " << m_near << std::endl;
		stream << Tab() << "Far: " << m_far << std::endl;
		stream << Tab() << "Focus: " << m_focus << std::endl;
		stream << Tab() << "Scale: " << m_scale << std::endl;
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}