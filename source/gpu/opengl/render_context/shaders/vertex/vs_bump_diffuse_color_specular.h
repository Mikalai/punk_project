#ifndef VS_BUMP_DIFFUSE_COLOR_SPECULAR_H
#define VS_BUMP_DIFFUSE_COLOR_SPECULAR_H

#include "../shader.h"
#include "../light_source_parameters.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsBumpMappingDiffuseColorSpecular : public Shader
        {
        public:
            VsBumpMappingDiffuseColorSpecular();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uWorld;
            unsigned uViewWorld;
            unsigned uView;
            unsigned uProj;
            unsigned uNormalMatrix;
            unsigned uTextureMatrix;
            LightSourceShaderParameters uLight;
        };
    }
}

#endif // VS_BUMP_DIFFUSE_COLOR_SPECULAR_H
