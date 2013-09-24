#include <sstream>
#include "fs_per_fragment_lighting_tex_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsPerFragmentLightingTextureDiffuse::FsPerFragmentLightingTextureDiffuse()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + System::string(GetShaderFile(ShaderCollection::FragmentLightPerFragmentTextureDiffuse)));
        }

        void FsPerFragmentLightingTextureDiffuse::InitUniforms()
        {
            uView = m_rc->GetUniformLocation("uView");
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
            for (int i = 0; i != MAX_LIGHTS; ++i)
            {
                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].ambient_color";
                    uLight[i].ambient_color = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].attenuation_constant";
                    uLight[i].attenuation_constant = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].attenuation_linear";
                    uLight[i].attenuation_linear = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].attenuation_model";
                    uLight[i].attenuation_model = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].attenuation_quadric";
                    uLight[i].attenuation_quadric = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].diffuse_color";
                    uLight[i].diffuse_color = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].direction";
                    uLight[i].direction = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].position";
                    uLight[i].position = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].spot";
                    uLight[i].spot = m_rc->GetUniformLocation(stream.str().c_str());
                }

                {
                    std::stringstream stream;
                    stream << "uLight[" << i << "].type";
                    uLight[i].type = m_rc->GetUniformLocation(stream.str().c_str());
                }
            }
        }

        void FsPerFragmentLightingTextureDiffuse::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);

            for (unsigned i = 0; i != params.light_state->m_used_lights; ++i)
            {
                m_rc->SetUniformVector4f(uLight[i].direction, params.light_state->m_lights[i].GetDirection());
                m_rc->SetUniformVector4f(uLight[i].position, params.light_state->m_lights[i].GetPosition());
                m_rc->SetUniformVector4f(uLight[i].diffuse_color, params.light_state->m_lights[i].GetDiffuseColor());
                m_rc->SetUniformVector4f(uLight[i].ambient_color, params.light_state->m_lights[i].GetAmbientColor());
                m_rc->SetUniformFloat(uLight[i].attenuation_constant, params.light_state->m_lights[i].GetLightConstantAttenuation());
                m_rc->SetUniformFloat(uLight[i].attenuation_linear, params.light_state->m_lights[i].GetLightLinearAttenuation());
                m_rc->SetUniformFloat(uLight[i].attenuation_quadric, params.light_state->m_lights[i].GetLightQuadricAttenuation());
                m_rc->SetUniformFloat(uLight[i].spot, params.light_state->m_lights[i].GetSpotExponent());
                m_rc->SetUniformInt(uLight[i].type, (int)params.light_state->m_lights[i].GetType());
                m_rc->SetUniformInt(uLight[i].attenuation_model, (int)params.light_state->m_lights[i].GetLightAttenuation());
            }
        }

        int64_t FsPerFragmentLightingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
