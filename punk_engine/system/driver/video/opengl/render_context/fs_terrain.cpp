#include "fs_terrain.h"
#include "../../../../environment.h"

namespace OpenGL
{
	ShaderTerrainFragment::ShaderTerrainFragment()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.frag");
	}
}