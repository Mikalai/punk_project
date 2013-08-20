#include "fs_text_solid.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsTextSolid::FsTextSolid()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentTextSolidColor));
        }

        void FsTextSolid::InitUniforms()
        {
            uTextMap = m_rc->GetUniformLocation("uTextMap");
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
        }

        void FsTextSolid::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_text_color);
            m_rc->SetUniformInt(uTextMap, params.texture_state->m_text_map_slot);
        }

        int64_t FsTextSolid::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
