#include "vs_solid_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
        VsSolid::VsSolid()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::VertexSolidColor));
		}

        void VsSolid::InitUniforms()
		{
            uViewWorld = m_rc->GetUniformLocation("uViewWorld");
			uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
		}

        void VsSolid::BindParameters(const CoreState& params)
		{
            auto view_world = params.view_state->m_view * params.batch_state->m_world;
            auto proj_view_world = params.view_state->m_projection * view_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
            m_rc->SetUniformMatrix4f(uViewWorld, view_world);
		}

        int64_t VsSolid::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value();
		}
	}
}
