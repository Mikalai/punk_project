#include "fs_grass.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		FragmentShaderGrass::FragmentShaderGrass()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"grass_330.frag");
		}
	}
}
