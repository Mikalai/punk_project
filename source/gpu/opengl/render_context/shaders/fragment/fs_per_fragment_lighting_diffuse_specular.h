#ifndef FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H
#define FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsPerFragmentLightingDiffuseSpecular : public Shader
        {
        public:
            FsPerFragmentLightingDiffuseSpecular();

        private:

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uView;
            unsigned uCameraWorldPosition;
            MaterialShaderParameters uMaterial;
            LightSourceShaderParameters uLight[MAX_LIGHTS];
        };
    }
}

#endif // FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H
