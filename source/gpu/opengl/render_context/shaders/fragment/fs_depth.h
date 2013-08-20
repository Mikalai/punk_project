#ifndef FS_DEPTH_H
#define FS_DEPTH_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsDepth : public Shader
        {
        public:
            FsDepth();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:            
        };
    }
}

#endif // FS_DEPTH_H
