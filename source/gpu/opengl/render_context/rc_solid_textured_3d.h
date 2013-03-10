#ifndef _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D
#define _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D

#include "gl_render_context.h"
#include "shaders/vertex/vs_transformed_textured_3d.h"
#include "shaders/fragment/fs_solid_textured.h"

namespace GPU
{
	namespace OpenGL
	{

		template<> class RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;
			unsigned uDiffuseMap;
			unsigned uTextureMatrix;

		public:

			RenderContextPolicy();
			virtual ~RenderContextPolicy();
			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& params) override;
			VertexAttributes GetRequiredAttributesSet() const override;
			void Begin() override;
			void End() override;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D