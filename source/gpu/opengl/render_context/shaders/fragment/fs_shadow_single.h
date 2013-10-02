#ifndef SHADOW_SINGLE_H
#define SHADOW_SINGLE_H

#include "../shader.h"
#include "../fog_parameters.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsShadowSingle : public Shader
        {
        public:
            FsShadowSingle();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseMap;
            unsigned uFarDistance;
            unsigned uShadowTextureArray;
            unsigned uShadowMatrix[4];
            unsigned uFar;
            unsigned uNear;
            FogShaderParameters uFog;
        };
    }
}

#endif // SHADOW_SINGLE_H
