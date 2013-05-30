#include "vs_solid_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderSolid::VertexShaderSolid()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::VertexSolidColor));
		}

		void VertexShaderSolid::InitUniforms()
		{
			uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
		}

		void VertexShaderSolid::BindParameters(const CoreState& params)
		{
			auto m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
			m_rc->SetUniformMatrix4f(uProjViewWorld, &m[0]);
		}

		int64_t VertexShaderSolid::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value();
		}
	}
}
