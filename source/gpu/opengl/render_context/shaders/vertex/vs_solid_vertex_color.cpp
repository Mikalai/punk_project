#include "vs_solid_vertex_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderSolidVertexColor::VertexShaderSolidVertexColor()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::VertexSolidVertexColor));
		}

		void VertexShaderSolidVertexColor::InitUniforms()
		{
			uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
		}

		void VertexShaderSolidVertexColor::BindParameters(const CoreState& params)
		{
			auto m = params.m_projection * params.m_view * params.m_world;
			m_rc->SetUniformMatrix4f(uProjViewWorld, m);
		}

		int64_t VertexShaderSolidVertexColor::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value() | VertexComponent::Color::Value();
		}
	}
}
