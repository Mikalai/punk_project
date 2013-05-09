#include "gpu_state.h"

namespace GPU
{
	CoreState::CoreState()
	{
		m_line_width = 1;
		m_point_size = 1;
		m_clear_depth = 1;
		m_depth_test = true;
		m_enable_lighting = false;
		m_enable_diffuse_shading = true;
		m_color_buffer = nullptr;
		m_depth_buffer = nullptr;
		m_diffuse_map_1 = nullptr;
		m_diffuse_map_0 = nullptr;
		m_normal_map = nullptr;
		m_height_map = nullptr;
		m_specular_map = nullptr;
		m_text_map = nullptr;
		m_light_constant_attenuation = 1;
		m_light_linear_attenuation = 0;
		m_light_quadric_attenuation = 0;
	}

	CoreState::~CoreState()
	{
		//	do not delete pointers, because they are owned by someone else
	}

	CoreState* CoreState::Clone()
	{
		return new CoreState(*this);
	}
}
