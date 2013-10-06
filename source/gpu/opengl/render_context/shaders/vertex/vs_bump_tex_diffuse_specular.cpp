#include "vs_bump_tex_diffuse_specular.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../../../../system/folder.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsBumpMappingTextureDiffuseSpecular::VsBumpMappingTextureDiffuseSpecular()
            : Shader(ShaderType::Vertex)
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            const char* names[] = {"/light.glsl"};
            CookFromFileWithHeaders(GetShaderFile(ShaderCollection::VertexBumpMappingTextureDiffuseSpecular), 1, names);
        }

        void VsBumpMappingTextureDiffuseSpecular::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uWorld = m_rc->GetUniformLocation("uWorld");
            uLight = m_rc->GetUniformLightLocation("uLight");
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
            uView = m_rc->GetUniformLocation("uView");
            uProj = m_rc->GetUniformLocation("uProj");
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
        }

        void VsBumpMappingTextureDiffuseSpecular::BindParameters(const CoreState& params)
        {
            const Math::mat4 vw = params.view_state->m_view * params.batch_state->m_world;
            const Math::mat4 pvw = params.view_state->m_projection * vw;
            const Math::mat3 normal_matrix = vw.RotationPart().Transposed().Inversed();
            m_rc->SetUniformMatrix4f(uProjViewWorld, pvw);
            m_rc->SetUniformMatrix4f(uViewWorld, vw);
            m_rc->SetUniformMatrix4f(uWorld, params.batch_state->m_world);
            m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
            m_rc->SetUniformMatrix4f(uProj, params.view_state->m_projection);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);
            m_rc->SetUniformLight(uLight, params.light_state->m_lights[0]);
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
        }

        int64_t VsBumpMappingTextureDiffuseSpecular::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Normal::Value()
                    | VertexComponent::Texture0::Value()
                    | VertexComponent::Tangent::Value()
                    | VertexComponent::Bitangent::Value();
        }
    }
}
