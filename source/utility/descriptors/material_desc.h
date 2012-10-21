#ifndef _H_PUNK_VIRTUAL_MATERIAL_DESC
#define _H_PUNK_VIRTUAL_MATERIAL_DESC

#include "../../config.h"
#include "../../string/string.h"
#include "../../math/vec3.h"

namespace Utility
{
	class PUNK_ENGINE MaterialDesc 
	{
	public:
		System::string m_diffuse_map;
		System::string m_normal_map;
		float m_alpha;
		float m_ambient;
		Math::vec3 m_diffuse_color;
		Math::vec3 m_specular_color;
		float m_specular_factor;
		System::string m_name;
		float m_diffuse_intensity;
		float m_darkness;
		float m_diffuse_fresnel;
		float m_diffuse_fresnel_factor;
		float m_emit;
		Math::vec3 m_mirror_color;
		float m_roughness;
		float m_specular_alpha;
		float m_specular_intensity;
		float m_specular_index_of_refraction;
		float m_specular_slope;
		float m_translucency;

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_MATERIAL_DESC
