#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING_SOLID
#define _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING_SOLID

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsSkinningDepth : public Shader
        {
        public:
            VsSkinningDepth();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uBones[64];
        };
    }
}

#endif
