#ifndef FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
#define FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsPerFragmentLightingDiffuse : public Shader
        {
        public:
            FsPerFragmentLightingDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseColor;
            unsigned uView;
            LightSourceShaderParameters uLight[MAX_LIGHTS];
        };
    }
}

#endif // FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
