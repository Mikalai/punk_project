#ifdef USE_SOLID_TEXTURE_3D_RC

#ifndef _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D
#define _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D

#include "gl_render_context.h"

namespace GPU
{
	namespace OpenGL
	{

		template<> class RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>: public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseMap;
			unsigned uDiffuseColor;
			unsigned uTextureMatrix;

		public:

			RenderContextPolicy();
			virtual ~RenderContextPolicy();
			void InitUniforms() override;
			void BindParameters(const CoreState& params) override;
			int64_t GetRequiredAttributesSet() const override;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D

#endif  //  USE_SOLID_TEXTURE_3D_RC
