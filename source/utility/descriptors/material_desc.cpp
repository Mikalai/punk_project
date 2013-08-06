#include "material_desc.h"
#include "../../system/logger.h"

namespace Utility
{
	std::wostream& MaterialDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Diffuse map: " << m_diffuse_map.Data() << std::endl;
		stream << Tab() << "Normal map: " << m_normal_map.Data() << std::endl;
		stream << Tab() << "Alpha: " << m_alpha << std::endl;
		stream << Tab() << "Ambient: " << m_ambient << std::endl;
		stream << Tab() << "Diffuse color: " << m_diffuse_color.out_formatted(stream) << std::endl;
		stream << Tab() << "Specular color: " << m_specular_color.out_formatted(stream) << std::endl;
		stream << Tab() << "Specular factor: " << m_specular_factor << std::endl;
		stream << Tab() << "Name: " << m_name.Data() << std::endl;
		stream << Tab() << "Diffuse intensity: " << m_diffuse_intensity << std::endl;
		stream << Tab() << "Darkness: " << m_darkness << std::endl;
		stream << Tab() << "Diffuse fresnel: " << m_diffuse_fresnel << std::endl;
		stream << Tab() << "Diffuse fresnel factor: " << m_diffuse_fresnel_factor << std::endl;
		stream << Tab() << "Emittion: " << m_emit << std::endl;
		stream << Tab() << "Mirror color: " << m_mirror_color.out_formatted(stream) << std::endl;
		stream << Tab() << "Roughness: " << m_roughness << std::endl;
		stream << Tab() << "Specular alpha: " << m_specular_alpha << std::endl;
		stream << Tab() << "Specular intensity: " << m_specular_intensity << std::endl;
		stream << Tab() << "Specular index of refraction: " << m_specular_index_of_refraction << std::endl;
		stream << Tab() << "Specular slope: " << m_specular_slope << std::endl;
		stream << Tab() << "Translucency: " << m_translucency << std::endl;
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}