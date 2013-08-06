#include "fs_bump_shadow_map.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsBumpShadowMap::FsBumpShadowMap()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentBumpMappingShadowMap));
        }

        void FsBumpShadowMap::InitUniforms()
        {
            uAmbient = m_rc->GetUniformLocation("uAmbient");
            uSpecular = m_rc->GetUniformLocation("uSpecular");
            uDiffuse = m_rc->GetUniformLocation("uDiffuse");
            uSpecularPower = m_rc->GetUniformLocation("uSpecularPower");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
            uNormalMap = m_rc->GetUniformLocation("uNormalMap");
            uDepthMap = m_rc->GetUniformLocation("uDepthMap");
            uNear = m_rc->GetUniformLocation("uNear");
            uFar = m_rc->GetUniformLocation("uFar");
        }

        void FsBumpShadowMap::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuse, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformVector4f(uAmbient, params.batch_state->m_material.m_ambient_color);
            m_rc->SetUniformVector4f(uSpecular, params.batch_state->m_material.m_specular_color);
            m_rc->SetUniformFloat(uSpecularPower, params.batch_state->m_material.m_specular_factor);
            Math::PerspectiveDecoder d(params.light_state->m_lights[0].GetProjectionMatrix());
            m_rc->SetUniformFloat(uNear, d.GetNearZ());
            m_rc->SetUniformFloat(uFar, d.GetFarZ());
            m_rc->SetUniformInt(uDiffuseMap, 0);
            m_rc->SetUniformInt(uNormalMap, 1);
            m_rc->SetUniformInt(uDepthMap, 2);
        }

        int64_t FsBumpShadowMap::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
