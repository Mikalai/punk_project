#ifndef _H_PUNK_OPENGL_FRAGMENT_SHADER_BUMP
#define _H_PUNK_OPENGL_FRAGMENT_SHADER_BUMP

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
        class FsBumpMappingTextureDiffuse : public Shader
		{
		public:
            FsBumpMappingTextureDiffuse();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uAmbient;
            unsigned uSpecular;
            unsigned uDiffuse;
            unsigned uSpecularPower;
            unsigned uDiffuseMap;
            unsigned uNormalMap;
		};
	}
}

#endif
