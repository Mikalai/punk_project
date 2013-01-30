#include "gpu_state.h"
#include "../../virtual/module.h"

namespace GPU
{
	CoreState::CoreState()
	{
		m_depth_test = true;
		m_blending = false;
		m_line_smooth = true;
		m_multisample = true;
		m_polygon_smooth = true;
		m_wireframe = false;
		m_enable_shadows = false;
		m_enable_lighting = true;
	}
}
