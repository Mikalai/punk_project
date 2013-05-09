#ifdef USE_PAINTER_RC

#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_PAINTER
#define _H_PUNK_OPENGL_RENDER_CONTEXT_PAINTER

#include "gl_render_context.h"
#include "shaders/vertex/vs_painter.h"
#include "shaders/fragment/fs_painter.h"

namespace GPU
{
	namespace OpenGL
	{
        /**********************************************************************************************
        *			PAINTER RENDER
        **********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader> : public OpenGLRenderContext
		{	
		public:
			RenderContextPolicy();
			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& pparams) override;
			int64_t GetRequiredAttributesSet() const override;
			virtual void Begin() override;
			virtual void End() override;

		private:
			unsigned uWorld;
			unsigned uDiffuseColor;
			unsigned uTextureMatrix;
			unsigned uTextColor;
			unsigned uUseTexture;
			unsigned uDiffuseMap;
			unsigned uTextMap;

		};
	}
}
#endif

#endif  //  USE_PAINTER_RC
