#ifndef _H_PUNK_OPENGL_SHADER_TRANSFORM_TEXTURED_3D
#define _H_PUNK_OPENGL_SHADER_TRANSFORM_TEXTURED_3D

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsTexture3D : public Shader
        {
        public:
            VsTexture3D();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uTextureMatrix;
        };
    }
}

#endif
