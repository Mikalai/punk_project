#ifndef FS_BUMP_SHADOW_MAP_H
#define FS_BUMP_SHADOW_MAP_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsBumpShadowMap : public Shader
        {
        public:
            FsBumpShadowMap();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uAmbient;
            unsigned uSpecular;
            unsigned uDiffuse;
            unsigned uSpecularPower;
            unsigned uDiffuseMap;
            unsigned uNormalMap;
            unsigned uDepthMap;
            unsigned uNear;
            unsigned uFar;
        };
    }
}

#endif // FS_BUMP_SHADOW_MAP_H
