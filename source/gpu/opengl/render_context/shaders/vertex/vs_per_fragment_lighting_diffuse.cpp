#include "vs_per_fragment_lighting_diffuse.h"

#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        VsPerFragmentLightingDiffuse::VsPerFragmentLightingDiffuse()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerFragmentTextureDiffuse));
        }

        void VsPerFragmentLightingDiffuse::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
        }

        void VsPerFragmentLightingDiffuse::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
        }

        int64_t VsPerFragmentLightingDiffuse::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value();
        }
    }
}
