#include "fs_solid_color.h"
#include "../../../../environment.h"

namespace OpenGL
{
	ShaderSolidColor::ShaderSolidColor()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"solid_color_3d_330.frag");
	}
}