#include "fs_depth.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../../../../math/perspective_decoder.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsDepth::FsDepth()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentDepth));
        }

        void FsDepth::InitUniforms()
        {            
        }

        void FsDepth::BindParameters(const CoreState& params)
        {           
        }

        int64_t FsDepth::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
