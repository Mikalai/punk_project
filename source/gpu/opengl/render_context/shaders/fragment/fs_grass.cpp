#include "fs_grass.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderGrass::FragmentShaderGrass()
			: Shader(SHADER_FRAGMENT)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"grass_330.frag");
		}
	}
}