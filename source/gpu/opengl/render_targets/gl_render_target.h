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

			virtual void SetViewport(float x, float y, float width, float height);
			virtual bool Init(Properties* props);
			virtual void Activate();
			virtual void Deactivate();
			virtual ~OpenGLRenderTarget();

		protected:
			void ClearTarget();
		};
	}
}

#endif	//	_H_PUNK_GPU_OPENGL_RENDER_TARGET
