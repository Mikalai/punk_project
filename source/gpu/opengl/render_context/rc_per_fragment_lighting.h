#ifdef USE_LIGHT_PER_FRAGMENT_DIFFUSE

#ifndef RC_PER_FRAGMENT_LIGHTING_H
#define RC_PER_FRAGMENT_LIGHTING_H

#include "../../common/config.h"
#include "gl_render_context.h"

namespace GPU
{

	namespace OpenGL
	{
		template<> class RenderContextPolicy<
				ShaderCollection::VertexLightPerFragmentDiffuse,
				ShaderCollection::FragmentLightPerFragmentDiffuse,
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
			unsigned uSpotExponent[MAX_LIGHTS];
			unsigned uType[MAX_LIGHTS];	//	0 - point, 1 - linear
			unsigned uLightDirection[MAX_LIGHTS];


		public:
			RenderContextPolicy();
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;
		};

	}
}

#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#endif // RC_PER_FRAGMENT_LIGHTING_H
