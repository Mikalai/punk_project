#ifndef _PUNK_RENDER_STATE
#define _PUNK_RENDER_STATE

namespace Render
{
	class RenderState
	{
	public:
		static void DepthTest(bool value);
		static void StencilTest(bool value);
		static void RenderModeWireframe();
		static void RenderModeFill();
		static void RenderModePoint();
	};
}

#endif