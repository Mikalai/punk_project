#include "vs_per_fragment_lighting_tex_diffuse_specular.h"

#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        VsPerFragmentLightingTextureDiffuseSpecular::VsPerFragmentLightingTextureDiffuseSpecular()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerFragmentTextureDiffuseSpecular));
        }

        void VsPerFragmentLightingTextureDiffuseSpecular::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uWorldTransposedInversed = m_rc->GetUniformLocation("uWorldTransposedInversed");
            uWorld = m_rc->GetUniformLocation("uWorld");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
        }

        void VsPerFragmentLightingTextureDiffuseSpecular::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 world = params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uWorldTransposedInversed, normal_matrix);
            m_rc->SetUniformMatrix4f(uWorld, world);
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
        }

        int64_t VsPerFragmentLightingTextureDiffuseSpecular::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value();
        }

    }
}
