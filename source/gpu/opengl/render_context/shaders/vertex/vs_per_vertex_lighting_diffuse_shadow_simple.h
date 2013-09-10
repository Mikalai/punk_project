#ifndef VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
#define VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        //  Vertex shader: per vertex lighting with diffuse texture and single shadowing
        class VsPerVertexLightingDiffuseShadowSimple : public Shader
        {
        public:
            VsPerVertexLightingDiffuseShadowSimple();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProj;
            unsigned uView;
            unsigned uWorld;
            unsigned uProjViewWorld;            
            unsigned uNormalMatrix;
            unsigned uDiffuseColor;
            unsigned uLightsCount;
            LightSourceShaderParameters uLight[MAX_LIGHTS];
        };
    }
}

#endif // VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
