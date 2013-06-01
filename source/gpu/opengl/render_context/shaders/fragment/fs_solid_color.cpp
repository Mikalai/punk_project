#include "fs_solid_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderSolid::FragmentShaderSolid()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidColor));
		}

		void FragmentShaderSolid::InitUniforms()
		{
			uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
		}

		void FragmentShaderSolid::BindParameters(const CoreState& params)
		{
			m_rc->SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);
		}

		int64_t FragmentShaderSolid::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
