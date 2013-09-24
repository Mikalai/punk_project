#include <sstream>
#include "vs_per_vertex_lighting_tex_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsPerVertexLightingTextureDiffuse::VsPerVertexLightingTextureDiffuse()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerVertexTextureDiffuse));
        }

        void VsPerVertexLightingTextureDiffuse::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uView = m_rc->GetUniformLocation("uView");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");

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

        void VsPerVertexLightingTextureDiffuse::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);

            for (int i = 0; i != params.light_state->m_used_lights; ++i)
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

        int64_t VsPerVertexLightingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value();
        }
    }
}
