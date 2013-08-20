#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING
#define _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
        class VsSkinningBump : public Shader
        {
        public:
            VsSkinningBump();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uNormalMatrix;
            unsigned uView;
            unsigned uProjViewWorld;
            unsigned uViewWorld;
            unsigned uLightPosition;
            unsigned uTextureMatrix;

            unsigned uBones[64];
        };
	}
}

#endif
