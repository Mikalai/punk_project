#ifndef _H_PUNK_UTILITY_POINT_LIGHT_DESC
#define _H_PUNK_UTILITY_POINT_LIGHT_DESC

#include "../../math/vec3.h"
#include "../../string/string.h"

namespace Utility
{
	class LightDesc
	{
	public:
		System::string m_type;
		System::string m_name;
		Math::vec3 m_color;
		float m_distance;
		float m_energy;
		System::string m_fall_off_type;
		float m_linear_attenuation;
		float m_quadratic_attenuation;

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	 _H_PUNK_UTILITY_POINT_LIGHT_DESC