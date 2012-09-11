#include "fs_terrain.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	FragmentShaderTerrain::FragmentShaderTerrain()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.frag");
	}
}