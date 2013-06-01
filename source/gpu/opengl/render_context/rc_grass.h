#ifdef USE_GRASS_RC

#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS

#include "gl_render_context.h"
#include "shaders/vertex/vs_grass.h"
#include "shaders/fragment/fs_grass.h"

namespace GPU
{
	namespace OpenGL
	{
        /**********************************************************************************************
        *			GRASS RENDER 3D
        **********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjView;
			unsigned uHeightMap;
			unsigned uPosition;
			unsigned uTime;
			unsigned uWindStrength;
			unsigned uWindDirection;
			unsigned uDiffuseColor;
			unsigned uDiffuseMap;

		public:

			RenderContextPolicy();
			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& pparams) override;
			int64_t GetRequiredAttributesSet() const override;
			void Begin() override;
			void End() override;
		};
	}
}

#endif

#endif  //  USE_GRASS_RC
