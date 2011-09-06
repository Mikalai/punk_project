#include "render_surface_win32.h"

namespace Video
{
	void RenderSurface::EnableDepthTest(bool value)
	{
		m_depth_test = value;
	}

	void RenderSurface::EnableStencilTest(bool value)
	{
		m_stencil_test = value;
	}

	void RenderSurface::SetPixel(int x, int y, const Video::PixelRGBA &p, float depth, unsigned int stencil)
	{
		if (m_enable_depth_test)
		{
			if (m_depth_buffer.At(x, y) < depth)
				return;
			m_depth_buffer.At(x, y) = depth;
		}

		m_color_buffer.At(x, y) = p;
	}

}