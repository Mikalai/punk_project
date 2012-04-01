#include "fs_solid_textured.h"
#include "../../../../environment.h"

namespace OpenGL
{
	ShaderSolidTextured::ShaderSolidTextured()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"textured_2d_330.frag");
	}
}