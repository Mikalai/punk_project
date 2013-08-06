#ifndef FS_TEXT_SOLID_H
#define FS_TEXT_SOLID_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsTextSolid : public Shader
        {
        public:
            FsTextSolid();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseColor;
            unsigned uTextMap;
        };
    }
}

#endif // FS_TEXT_SOLID_H
