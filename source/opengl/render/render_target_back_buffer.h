#ifndef _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER
#define _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER

#include "render_target.h"

namespace OpenGL
{
	class PUNK_ENGINE RenderTargetBackBuffer : public RenderTarget
	{
	public:

		struct PUNK_ENGINE RenderTargetBackBufferProperties : public Properties
		{
			RenderTargetBackBufferProperties();
		};

	public:
		virtual bool Init(Properties* props);
		virtual void Activate();
		virtual void Deactivate();		
		virtual ~RenderTargetBackBuffer();
	};
}

#endif	//	_H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER