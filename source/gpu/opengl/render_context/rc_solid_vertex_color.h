#ifdef USE_SOLID_VERTEX_COLOR_RC

#ifndef RC_SOLID_VERTEX_COLOR_H
#define RC_SOLID_VERTEX_COLOR_H

#include "gl_render_context.h"

namespace GPU
{

	namespace OpenGL
	{		
		template<> class RenderContextPolicy<
				ShaderCollection::VertexSolidVertexColor,
				ShaderCollection::FragmentSolidVertexColor,
				ShaderCollection::No> : public OpenGLRenderContext
		{
			unsigned uProjViewWorld;

		public:
			RenderContextPolicy();
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;
		};

	}
}

#endif // RC_SOLID_VERTEX_COLOR_H

#endif  //    USE_SOLID_VERTEX_COLOR_RC
