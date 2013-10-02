#ifndef FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H
#define FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H

#include "../shader.h"
#include "../light_source_parameters.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsPerFragmentLightingTextureDiffuse : public Shader
        {
        public:
            FsPerFragmentLightingTextureDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uView;
            unsigned uDiffuseColor;
            unsigned uDiffuseMap;
            LightSourceShaderParameters uLight[MAX_LIGHTS];

        };
    }
}

#endif // FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_H
