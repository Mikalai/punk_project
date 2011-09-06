#include "render_state.h"
#include "../driver/video/driver.h"

namespace Render
{
	void RenderState::DepthTest(bool value)
	{
		if (value)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void RenderState::StencilTest(bool value)
	{
		if (value)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);
	}

	void RenderState::RenderModeFill()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void RenderState::RenderModePoint()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	void RenderState::RenderModeWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}