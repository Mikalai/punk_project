#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE

#ifndef RC_PER_VERTEX_LIGHTING_H
#define RC_PER_VERTEX_LIGHTING_H

#include "../../common/config.h"
#include "gl_render_context.h"

namespace GPU
{

	namespace OpenGL
	{
		template<> class RenderContextPolicy<
				ShaderCollection::VertexLightPerVertexDiffuse,
				ShaderCollection::FragmentLightPerVertexDiffuse,
				ShaderCollection::No> : public OpenGLRenderContext
		{
			unsigned uNormalMatrix;
			unsigned uViewWorld;
			unsigned uProjViewWorld;
			unsigned uView;
			unsigned uDiffuseColor;

			unsigned uConstantAttenuation[MAX_LIGHTS];
			unsigned uLinearAttenuation[MAX_LIGHTS];
			unsigned uQuadricAttenuation[MAX_LIGHTS];
			unsigned uMode[MAX_LIGHTS];
			unsigned uLightPosition[MAX_LIGHTS];
			unsigned uLightDiffuse[MAX_LIGHTS];


		public:
			RenderContextPolicy();
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;
		};

	}
}

#endif // RC_PER_VERTEX_LIGHTING_H

#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE
