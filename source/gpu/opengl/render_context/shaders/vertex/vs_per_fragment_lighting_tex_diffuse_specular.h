#ifndef VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H
#define VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsPerFragmentLightingTextureDiffuseSpecular : public Shader
        {
        public:
            VsPerFragmentLightingTextureDiffuseSpecular();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uWorldTransposedInversed;
            unsigned uWorld;
            unsigned uProjViewWorld;
            unsigned uTextureMatrix;
        };

    }
}

#endif // VS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H
