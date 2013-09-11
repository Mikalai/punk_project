#include "fs_bump.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
        FsBumpMappingTextureDiffuse::FsBumpMappingTextureDiffuse()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentBumpMapping));
        }

        void FsBumpMappingTextureDiffuse::InitUniforms()
        {
            uAmbient = m_rc->GetUniformLocation("uAmbient");
            uSpecular = m_rc->GetUniformLocation("uSpecular");
            uDiffuse = m_rc->GetUniformLocation("uDiffuse");
            uSpecularPower = m_rc->GetUniformLocation("uSpecularPower");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
            uNormalMap = m_rc->GetUniformLocation("uNormalMap");
        }

        void FsBumpMappingTextureDiffuse::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuse, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformVector4f(uAmbient, params.batch_state->m_material.m_ambient_color);
            m_rc->SetUniformVector4f(uSpecular, params.batch_state->m_material.m_specular_color);
            m_rc->SetUniformFloat(uSpecularPower, params.batch_state->m_material.m_specular_factor);
            m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);
            m_rc->SetUniformInt(uNormalMap, params.texture_state->m_normal_map_slot);
        }

        int64_t FsBumpMappingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
	}
}
