#ifndef _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_DIFFUSE
#define _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_DIFFUSE

#include "..\shader.h"

namespace GPU
{
	namespace OpenGL
	{
        class VsPerVertexLightingDiffuse : public Shader
		{
		public:
            VsPerVertexLightingDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
            unsigned uView;

            unsigned uLightPosition[MAX_LIGHTS];
            unsigned uLightDirection[MAX_LIGHTS];
            unsigned uLightDiffuse[MAX_LIGHTS];

            unsigned uConstantAttenuation[MAX_LIGHTS];
            unsigned uLinearAttenuation[MAX_LIGHTS];
            unsigned uQuadricAttenuation[MAX_LIGHTS];

            unsigned uMode[MAX_LIGHTS]; //	0 - Constant, 1 - Linear, 2 - Quadric
            unsigned uSpotExponent[MAX_LIGHTS];
            unsigned uType[MAX_LIGHTS];	//	0 - point, 1 - linear

		};
	}
}

#endif
