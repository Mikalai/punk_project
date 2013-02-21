#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D

#include "gl_render_context.h"
#include "shaders/vertex/vs_solid_color.h"
#include "shaders/fragment/fs_solid_color.h"

namespace GPU
{
	namespace OpenGL
	{
		template<> class RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader> : public OpenGLRenderContext 
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;

		public:

			RenderContextPolicy();
			virtual ~RenderContextPolicy();
			virtual void Init() override;
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual VertexAttributes GetRequiredAttributesSet() const override;
			virtual void Begin() override;
			virtual void End() override;
		};
	}
}

#endif