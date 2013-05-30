#include "gpu_material.h"

namespace GPU
{
	Material::Material()
		: m_diffuse_color(0.8f, 0.8f, 0.8f, 1.0f)
		, m_specular_color(1.0f, 1.0f, 1.0f, 1.0f)
		, m_text_color(1, 1, 1,  1)
		, m_no_diffuse_texture_color(1,1,1,1)
		, m_specular_factor(128)
		, m_emit_color(1,1,1,1)
		, m_diffuse_intensity(1.0f)
		, m_darkness(0.0f)
		, m_diffuse_fresnel(1.0f)
		, m_diffuse_fresnel_factor(0.0f)
		, m_emit(0.0f)
		, m_mirror_color(0.0f, 0.0f, 0.0f, 1.0f)
		, m_roughness(0.0f)
		, m_specular_intensity(128.0f)
		, m_specular_index_of_refraction(1.0f)
		, m_specular_slope(0.0f)
		, m_translucency(0.0f)
	{}
}
