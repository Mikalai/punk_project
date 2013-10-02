#ifndef _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_TEXTURE_DIFFUSE
#define _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_TEXTURE_DIFFUSE

#include "../shader.h"
#include "../light_source_parameters.h"

namespace Gpu
{
	namespace OpenGL
	{
        class VsPerVertexLightingTextureDiffuse : public Shader
		{
		public:
            VsPerVertexLightingTextureDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
            unsigned uView;
			unsigned uTextureMatrix;

            LightSourceShaderParameters uLight[MAX_LIGHTS];
		};
	}
}

#endif
