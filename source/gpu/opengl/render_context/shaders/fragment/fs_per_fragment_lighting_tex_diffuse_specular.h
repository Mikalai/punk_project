#ifndef FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H
#define FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H

#include "../shader.h"
#include "../material_parameters.h"
#include "../light_source_parameters.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsPerFragmentLightingTextureDiffuseSpecular : public Shader
        {
        public:
            FsPerFragmentLightingTextureDiffuseSpecular();

        private:

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uView;
            unsigned uCameraWorldPosition;
            MaterialShaderParameters uMaterial;
            LightSourceShaderParameters uLight[MAX_LIGHTS];
            unsigned uDiffuseMap;
        };
    }
}

#endif // FS_PER_FRAGMENT_LIGHTING_TEX_DIFFUSE_SPECULAR_H
