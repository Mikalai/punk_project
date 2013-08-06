#include "fs_terrain.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		FragmentShaderTerrain::FragmentShaderTerrain()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.frag");
		}
	}
}