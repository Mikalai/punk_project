#include "fs_solid_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
		FsShaderSolid::FsShaderSolid()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidColor));
		}

		void FsShaderSolid::InitUniforms()
		{
			uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
		}

		void FsShaderSolid::BindParameters(const CoreState& params)
		{
			m_rc->SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);
		}

		int64_t FsShaderSolid::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
