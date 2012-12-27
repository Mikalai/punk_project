#include "render_state.h"

namespace OpenGL
{
	CoreState::CoreState()
	{
		m_depth_test = true;
		m_blending = false;
		m_line_smooth = true;
		m_multisample = true;
		m_polygon_smooth = true;
		m_wireframe = false;
	}
}
