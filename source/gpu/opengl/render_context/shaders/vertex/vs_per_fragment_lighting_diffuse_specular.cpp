#include "vs_per_fragment_lighting_diffuse_specular.h"

#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        VsPerFragmentLightingDiffuseSpecular::VsPerFragmentLightingDiffuseSpecular()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerFragmentDiffuseSpecular));
        }

        void VsPerFragmentLightingDiffuseSpecular::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uWorldTransposedInversed = m_rc->GetUniformLocation("uWorldTransposedInversed");
            uWorld = m_rc->GetUniformLocation("uWorld");
        }

        void VsPerFragmentLightingDiffuseSpecular::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 world = params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uWorldTransposedInversed, normal_matrix);
            m_rc->SetUniformMatrix4f(uWorld, world);
        }

        int64_t VsPerFragmentLightingDiffuseSpecular::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value();
        }

    }
}
