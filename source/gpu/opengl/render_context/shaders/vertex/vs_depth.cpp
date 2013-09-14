#include "vs_depth.h"
#include "../../../../../system/folder.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        VsDepth::VsDepth()
            : Shader(ShaderType::Vertex)
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            CookFromFile(GetShaderFile(ShaderCollection::VertexDepth));
            f.Close();
        }

        void VsDepth::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
        }

        void VsDepth::BindParameters(const CoreState& params)
        {
            const Math::mat4 m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, m);
        }

        int64_t VsDepth::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value();
        }
    }
}
