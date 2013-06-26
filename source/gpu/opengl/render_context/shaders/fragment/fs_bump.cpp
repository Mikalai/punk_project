#include "fs_bump.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
        FsBumpMapping::FsBumpMapping()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentBumpMapping));
        }

        void FsBumpMapping::InitUniforms()
        {
            uAmbient = m_rc->GetUniformLocation("uAmbient");
            uSpecular = m_rc->GetUniformLocation("uSpecular");
            uDiffuse = m_rc->GetUniformLocation("uDiffuse");
            uSpecularPower = m_rc->GetUniformLocation("uSpecularPower");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
            uNormalMap = m_rc->GetUniformLocation("uNormalMap");
        }

        void FsBumpMapping::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuse, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformVector4f(uAmbient, params.batch_state->m_material.m_ambient_color);
            m_rc->SetUniformVector4f(uSpecular, params.batch_state->m_material.m_specular_color);
            m_rc->SetUniformFloat(uSpecularPower, params.batch_state->m_material.m_specular_factor);
            m_rc->SetUniformInt(uDiffuseMap, 0);
            m_rc->SetUniformInt(uNormalMap, 1);
        }

        int64_t FsBumpMapping::GetRequiredAttributesSet() const
        {
            return 0;
        }
	}
}
