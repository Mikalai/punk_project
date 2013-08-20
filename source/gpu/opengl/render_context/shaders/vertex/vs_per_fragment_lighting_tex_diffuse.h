#ifndef VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H
#define VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsPerFragmentLightingTextureDiffuse : public Shader
        {
        public:
            VsPerFragmentLightingTextureDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
            unsigned uTextureMatrix;
        };

    }
}

#endif // VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H
