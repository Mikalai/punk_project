#ifndef VS_SHADOW_H
#define VS_SHADOW_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        //  Vertex shader: per vertex lighting with diffuse texture and single shadowing
        class VsPvltdShadowSingle : public Shader
        {
        public:
            VsPvltdShadowSingle();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uWorld;
            unsigned uViewModel;
            unsigned uProj;
            unsigned uNormalMatrix;
            unsigned uDiffuseColor;
            unsigned uLightsCount;
            LightSourceShaderParameters uLight[MAX_LIGHTS];
        };
    }
}

#endif // VS_SHADOW_H
