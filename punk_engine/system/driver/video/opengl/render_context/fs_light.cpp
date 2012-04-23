#include "fs_light.h"
#include "../../../../environment.h"

namespace OpenGL
{
	FragmentShaderLight::FragmentShaderLight()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"per_vertex_lighting_330.frag");
	}
}