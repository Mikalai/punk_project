#include "fs_solid_vertex_color.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderSolidVertexColor::FragmentShaderSolidVertexColor()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidVertexColor));
		}

		void FragmentShaderSolidVertexColor::InitUniforms()
		{
		}

		void FragmentShaderSolidVertexColor::BindParameters(const CoreState& params)
		{
		}

		int64_t FragmentShaderSolidVertexColor::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
