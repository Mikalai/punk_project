#ifdef USE_SOLID_COLOR_RC

#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D

#include "gl_render_context.h"

namespace GPU
{
	namespace OpenGL
	{
        template<> class RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No> : public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;

		public:

			RenderContextPolicy();
			virtual ~RenderContextPolicy();
			virtual void Init() override;
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;
			virtual void Begin() override;
			virtual void End() override;
		};
	}
}

#endif

#endif  //  USE_SOLID_COLOR_3D_RC
