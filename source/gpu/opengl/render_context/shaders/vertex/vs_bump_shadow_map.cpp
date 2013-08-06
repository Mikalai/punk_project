#include "vs_bump_shadow_map.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsBumpShadowMap::VsBumpShadowMap()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexBumpMappingShadowMap));
        }

        void VsBumpShadowMap::InitUniforms()
        {
            uWorld = m_rc->GetUniformLocation("uWorld");
            uView = m_rc->GetUniformLocation("uView");
            uProj = m_rc->GetUniformLocation("uProj");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uLightPosition = m_rc->GetUniformLocation("uLightPosition");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
            uLightProjectionMatrix = m_rc->GetUniformLocation("uLightProjectionMatrix");
            uLightViewMatrix = m_rc->GetUniformLocation("uLightViewMatrix");
        }

        void VsBumpShadowMap::BindParameters(const CoreState& params)
        {
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            m_rc->SetUniformMatrix4f(uWorld, params.batch_state->m_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uProj, params.view_state->m_projection);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);
            m_rc->SetUniformVector3f(uLightPosition, params.light_state->m_lights[0].GetPosition().XYZ());
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
            m_rc->SetUniformMatrix4f(uLightProjectionMatrix, params.light_state->m_lights[0].GetProjectionMatrix());
            m_rc->SetUniformMatrix4f(uLightViewMatrix, params.light_state->m_lights[0].GetViewMatrix());
        }

        int64_t VsBumpShadowMap::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value()
                    | VertexComponent::Tangent::Value()
                    | VertexComponent::Bitangent::Value();
        }
    }
}
