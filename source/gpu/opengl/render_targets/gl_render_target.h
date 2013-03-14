#ifndef _H_PUNK_GPU_OPENGL_RENDER_TARGET
#define _H_PUNK_GPU_OPENGL_RENDER_TARGET

#include "../../common/render_target.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE OpenGLRenderTarget : public GPU::RenderTarget
		{
		public:

			void SetViewport(const Math::Rect& value) override;
			bool Init(Properties* props) override;
			void Activate() override;
			void Deactivate() override;

			virtual ~OpenGLRenderTarget();

		protected:
			void ClearTarget();
		};
	}
}

#endif	//	_H_PUNK_GPU_OPENGL_RENDER_TARGET
