#ifndef _H_PUNK_SOFT_RENDER_SURFACE_WIN32
#define _H_PUNK_SOFT_RENDER_SURFACE_WIN32

#include "buffer_win32.h"

namespace Video
{
	
	class RenderSurface
	{
		DepthBuffer m_depth_buffer;
		StencilBuffer m_stencil_buffer;
		ColorBuffer m_color_buffer;

		bool m_enable_depth_test;
		bool m_enable_stencil_test;		

	public:

		void EnableDepthTest(bool value);
		void EnableStencilTest(bool value);

		void SetPixel(int x, int y, const PixelRGBA& p, float depth = 0.0, unsigned stencil);
		void SetSize(int width, int height);
		int GetWidth() const;
		int GetHeight() const;
	};
}

#endif