#ifndef VS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
#define VS_PER_FRAGMENT_LIGHTING_DIFFUSE_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsPerFragmentLightingDiffuse : public Shader
        {
        public:
            VsPerFragmentLightingDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
        };
    }
}

#endif // VS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
