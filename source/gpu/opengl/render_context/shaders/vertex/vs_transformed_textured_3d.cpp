#include "vs_transformed_textured_3d.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsTexture3D::VsTexture3D()
            : Shader(ShaderType::Vertex)
            , uProjViewWorld(-1)
            , uTextureMatrix(-1)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexSolidTextured));
        }

        void VsTexture3D::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
            uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
        }

        void VsTexture3D::BindParameters(const CoreState& params)
        {
            auto m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, m);
            m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
        }

        int64_t VsTexture3D::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value()
                    | VertexComponent::Texture0::Value();
        }
    }
}
