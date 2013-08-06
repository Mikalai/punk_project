#include "fs_depth.h"
#include "../shader_type.h"
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
            uNear = m_rc->GetUniformLocation("uNear");
            uFar = m_rc->GetUniformLocation("uFar");
            uFilterType = m_rc->GetUniformLocation("uFilterType");
        }

        void FsDepth::BindParameters(const CoreState& params)
        {
            Math::PerspectiveDecoder d(params.view_state->m_projection);
            m_rc->SetUniformFloat(uFar, d.GetNearZ());
            m_rc->SetUniformFloat(uFar, d.GetFarZ());
            m_rc->SetUniformInt(uFilterType, (int)params.render_state->m_shadow_model);
        }

        int64_t FsDepth::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
