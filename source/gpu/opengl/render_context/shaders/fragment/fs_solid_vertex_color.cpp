#include "fs_solid_vertex_color.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
	namespace OpenGL
	{
		FsSolidVertexColor::FsSolidVertexColor()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidVertexColor));
		}

		void FsSolidVertexColor::InitUniforms()
		{
		}

		void FsSolidVertexColor::BindParameters(const CoreState& params)
		{
		}

		int64_t FsSolidVertexColor::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
