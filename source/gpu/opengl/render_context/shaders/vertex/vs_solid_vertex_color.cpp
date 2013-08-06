#include "vs_solid_vertex_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
		VsSolidVertexColor::VsSolidVertexColor()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::VertexSolidVertexColor));
		}

		void VsSolidVertexColor::InitUniforms()
		{
			uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
		}

		void VsSolidVertexColor::BindParameters(const CoreState& params)
		{
			auto m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
			m_rc->SetUniformMatrix4f(uProjViewWorld, m);
		}

		int64_t VsSolidVertexColor::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value() | VertexComponent::Color::Value();
		}
	}
}
