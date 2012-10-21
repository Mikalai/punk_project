#include "../../system/logger.h"
#include "light_desc.h"

namespace Utility
{
	std::wostream& LightDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		stream << Tab() << "Type: " << m_type.Data() << std::endl;
		stream << Tab() << "Color: " << m_color << std::endl;
		stream << Tab() << "Distance: " << m_distance << std::endl;
		stream << Tab() << "Energy: " << m_energy << std::endl;
		stream << Tab() << "Fall-off type: " << m_fall_off_type.Data() << std::endl;
		stream << Tab() << "Linear attenuation: " << m_linear_attenuation << std::endl;
		stream << Tab() << "Quadratic attenuation: " << m_quadratic_attenuation << std::endl;
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}