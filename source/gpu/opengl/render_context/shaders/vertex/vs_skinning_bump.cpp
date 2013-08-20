#include <sstream>
#include "vs_skinning_bump.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
        VsSkinningBump::VsSkinningBump()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexSkinningBump));
        }

        void VsSkinningBump::InitUniforms()
        {
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uLightPosition = m_rc->GetUniformLocation("uLightPosition");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
            uView = m_rc->GetUniformLocation("uView");

            for (int i = 0; i != MAX_BONES; ++i)
            {
                std::stringstream stream;
                stream << "uBones[" << i << "]";
                uBones[i] = m_rc->GetUniformLocation(stream.str().c_str());
            }
        }

        void VsSkinningBump::BindParameters(const CoreState& params)
        {
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
            m_rc->SetUniformVector3f(uLightPosition, params.light_state->m_lights[0].GetPosition().XYZ());
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

            int count = (params.batch_state->m_used_bones_count == -1) ? MAX_BONES : params.batch_state->m_used_bones_count;
            for (int i = 0; i != count; ++i)
            {
                m_rc->SetUniformMatrix4f(uBones[i], params.batch_state->m_bone_matrix[i]);
            }
        }

        int64_t VsSkinningBump::GetRequiredAttributesSet() const
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
