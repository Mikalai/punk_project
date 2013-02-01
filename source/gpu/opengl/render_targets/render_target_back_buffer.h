#ifndef _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER
#define _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER

#include "gl_render_target.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE RenderTargetBackBuffer : public OpenGLRenderTarget
		{
		public:

			struct PUNK_ENGINE RenderTargetBackBufferProperties : public RenderTarget::Properties
			{
				RenderTargetBackBufferProperties();
			};

		public:
			virtual bool Init(RenderTarget::Properties* props);
			virtual void Activate();
			virtual void Deactivate();		
			virtual ~RenderTargetBackBuffer();
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER