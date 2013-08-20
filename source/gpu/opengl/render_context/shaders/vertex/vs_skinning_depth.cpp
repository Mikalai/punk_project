#include <sstream>
#include "vs_skinning_depth.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsSkinningDepth::VsSkinningDepth()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexSkinningDepth));
        }

        void VsSkinningDepth::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");

            for (int i = 0; i != MAX_BONES; ++i)
            {
                std::stringstream stream;
                stream << "uBones[" << i << "]";
                uBones[i] = m_rc->GetUniformLocation(stream.str().c_str());
            }
        }

        void VsSkinningDepth::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);

            int count = (params.batch_state->m_used_bones_count == -1) ? MAX_BONES : params.batch_state->m_used_bones_count;
            for (int i = 0; i != count; ++i)
            {
                m_rc->SetUniformMatrix4f(uBones[i], params.batch_state->m_bone_matrix[i]);
            }
        }

        int64_t VsSkinningDepth::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::BoneID::Value()
                    | VertexComponent::BoneWeight::Value();
        }
    }
}
