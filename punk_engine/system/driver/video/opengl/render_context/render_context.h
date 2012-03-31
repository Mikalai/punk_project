#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC
#define _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC

#include "../config.h"
#include <memory>

namespace OpenGL
{
	class Shader;

	struct RenderContextImpl;

	class  MODULE_OPENGL RenderContext
	{		
	protected:
		std::auto_ptr<RenderContextImpl> impl_rc;
	public:
		RenderContext();
		RenderContext(const RenderContext& rc);
		RenderContext& operator = (const RenderContext& rc);

		void SetVertexShader(Shader* shader);
		void SetFragmentShader(Shader* shader);
		void SetGeometryShader(Shader* shader);

		void Begin();
		void End();

		RenderContext* Push();
		RenderContext* Pop();
	};
}

#endif