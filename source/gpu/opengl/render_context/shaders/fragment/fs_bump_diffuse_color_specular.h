#ifndef FS_BUMP_DIFFUSE_COLOR_SPECULAR_H
#define FS_BUMP_DIFFUSE_COLOR_SPECULAR_H

#include "../shader.h"
#include "../material_parameters.h"
#include "../light_source_parameters.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsBumpMappingDiffuseColorSpecular : public Shader
        {
        public:
            FsBumpMappingDiffuseColorSpecular();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            MaterialShaderParameters uMaterial;
            LightSourceShaderParameters uLight;
            unsigned uNormalMap;
        };
    }
}

#endif // FS_BUMP_DIFFUSE_COLOR_SPECULAR_H
