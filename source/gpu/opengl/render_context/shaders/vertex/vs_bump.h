#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_BUMP
#define _H_PUNK_OPENGL_VERTEX_SHADER_BUMP

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
        class VsBumpMappingTextureDiffuse : public Shader
		{
		public:
            VsBumpMappingTextureDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uWorld;
            unsigned uView;
            unsigned uProj;
            unsigned uNormalMatrix;
            unsigned uLightPosition;
            unsigned uTextureMatrix;
		};
	}
}

#endif
