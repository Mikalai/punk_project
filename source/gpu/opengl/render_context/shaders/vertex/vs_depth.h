#ifndef VS_DEPTH_H
#define VS_DEPTH_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsDepth : public Shader
        {
        public:
            VsDepth();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
        };
    }
}

#endif // VS_DEPTH_H
