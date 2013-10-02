#include "vs_per_fragment_lighting_tex_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        VsPerFragmentLightingTextureDiffuse::VsPerFragmentLightingTextureDiffuse()
            : Shader(ShaderType::Vertex)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerFragmentTextureDiffuse));
        }

        void VsPerFragmentLightingTextureDiffuse::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");            
        }

        void VsPerFragmentLightingTextureDiffuse::BindParameters(const CoreState& params)
        {
            const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
            const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
        }

        int64_t VsPerFragmentLightingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value();
        }
    }
}
