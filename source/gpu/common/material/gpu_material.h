#ifndef _H_PUNK_GPU_MATERIAL
#define _H_PUNK_GPU_MATERIAL

#include "../../../config.h"
#include "../../../math/vec4.h"

namespace Gpu
{
	class PUNK_ENGINE_API Material
	{	
	public:		

		Material();

		Math::vec4 m_diffuse_color;
		Math::vec4 m_text_color;
		Math::vec4 m_no_diffuse_texture_color;
		Math::vec4 m_specular_color;
		Math::vec4 m_mirror_color;
		Math::vec4 m_emit_color;
		float m_ambient_color;
		float m_specular_factor;
		float m_diffuse_intensity;
		float m_diffuse_fresnel;
		float m_diffuse_fresnel_factor;
		float m_emit;		
		float m_roughness;
		float m_specular_intensity;
		float m_specular_index_of_refraction;
		float m_specular_slope;
		float m_translucency;		
		float m_darkness;
	};
}

#endif	//	H_PUNK_GPU_MATERIAL
