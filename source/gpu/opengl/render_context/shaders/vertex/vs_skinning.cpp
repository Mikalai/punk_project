#include <sstream>
#include "vs_skinning.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
        VsSkinning::VsSkinning()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexSkinning));
        }

        void VsSkinning::InitUniforms()
        {
            uWorld = m_rc->GetUniformLocation("uWorld");
            uView = m_rc->GetUniformLocation("uView");
            uProj = m_rc->GetUniformLocation("uProj");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uLightPosition = m_rc->GetUniformLocation("uLightPosition");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
            for (int i = 0; i != MAX_BONES; ++i)
            {
                std::stringstream stream;
                stream << "uBones[" << i << "]";
                uBones[i] = m_rc->GetUniformLocation(stream.str().c_str());
            }
        }

        void VsSkinning::BindParameters(const CoreState& params)
        {
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uWorld, params.batch_state->m_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uProj, params.view_state->m_projection);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
            m_rc->SetUniformVector3f(uLightPosition, params.light_state->m_lights[0].GetPosition().XYZ());
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);

            int count = (params.batch_state->m_used_bones_count == -1) ? MAX_BONES : params.batch_state->m_used_bones_count;
            for (int i = 0; i != count; ++i)
            {
                m_rc->SetUniformMatrix4f(uBones[i], params.batch_state->m_bone_matrix[i]);
            }
        }

        int64_t VsSkinning::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value()
                    | VertexComponent::Tangent::Value()
                    | VertexComponent::Bitangent::Value()
                    | VertexComponent::BoneID::Value()
                    | VertexComponent::BoneWeight::Value();
        }	}
}
