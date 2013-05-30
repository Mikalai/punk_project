#include "vs_per_vertex_lighting_diffuse.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
    namespace OpenGL
    {
        VsPerVertexLightingDiffuse::VsPerVertexLightingDiffuse()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerVertexDiffuse));
        }

        void VsPerVertexLightingDiffuse::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uView = m_rc->GetUniformLocation("uView");

            for (int i = 0; i != MAX_LIGHTS; ++i)
            {
                {
                    std::stringstream stream;
                    stream << "uLightPosition[" << i << "]";
                    uLightPosition[i] = m_rc->GetUniformLocation(stream.str().c_str());
                }
                {
                    std::stringstream stream;
                    stream << "uLightDiffuse[" << i << "]";
                    uLightDiffuse[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uConstantAttenuation[" << i << "]";
                    uConstantAttenuation[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uLinearAttenuation[" << i << "]";
                    uLinearAttenuation[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uQuadricAttenuation[" << i << "]";
                    uQuadricAttenuation[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uMode[" << i << "]";
                    uMode[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uSpotExponent[" << i << "]";
                    uSpotExponent[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uType[" << i << "]";
                    uType[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
                {
                    std::stringstream stream;
                    stream << "uLightDirection[" << i << "]";
                    uLightDirection[i] = m_rc->GetUniformLocation(stream.str().c_str());;
                }
            }
        }

        void VsPerVertexLightingDiffuse::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

            for (int i = 0; i != MAX_LIGHTS; ++i)
            {
                m_rc->SetUniformVector4f(uLightPosition[i], params.light_state->m_lights[i].GetPosition());
                m_rc->SetUniformVector4f(uLightDiffuse[i], params.light_state->m_lights[i].GetDiffuseColor());
                m_rc->SetUniformVector4f(uLightDirection[i], params.light_state->m_lights[i].GetDirection());
                m_rc->SetUniformFloat(uConstantAttenuation[i], params.light_state->m_lights[i].GetLightConstantAttenuation());
                m_rc->SetUniformFloat(uLinearAttenuation[i], params.light_state->m_lights[i].GetLightLinearAttenuation());
                m_rc->SetUniformFloat(uQuadricAttenuation[i], params.light_state->m_lights[i].GetLightQuadricAttenuation());
                m_rc->SetUniformFloat(uSpotExponent[i], params.light_state->m_lights[i].GetSpotExponent());

                switch (params.light_state->m_lights[i].GetLightAttenuation())
                {
                case LightAttenuation::Constant:
                    m_rc->SetUniformInt(uMode[i], 0);
                    break;
                case LightAttenuation::Linear:
                    m_rc->SetUniformInt(uMode[i], 1);
                    break;
                case LightAttenuation::Quadratic:
                    m_rc->SetUniformInt(uMode[i], 2);
                    break;
                }

                switch (params.light_state->m_lights[i].GetType())
                {
                case LightType::Point:
                    m_rc->SetUniformInt(uType[i], 0);
                    break;
                case LightType::Spot:
                    m_rc->SetUniformInt(uType[i], 1);
                    break;
                }
            }
        }

        int64_t VsPerVertexLightingDiffuse::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value() | VertexComponent::Normal::Value();
        }
    }
}
