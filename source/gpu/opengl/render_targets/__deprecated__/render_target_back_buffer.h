#ifndef _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER
#define _H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER

#include "../../common/render_target.h"

namespace Gpu
{
	namespace OpenGL
	{
        class PUNK_ENGINE_API RenderTargetBackBuffer : public RenderTarget
		{
		public:		            
            RenderTargetBackBuffer(VideoDriver* driver);
            virtual void SetViewport(const Math::Rect& value) override;
            virtual void Activate() override;
            virtual void Deactivate() override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual ~RenderTargetBackBuffer();
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RENDER_TARGET_BACK_BUFFER
