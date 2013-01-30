#include "fs_solid_color.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderSolid::FragmentShaderSolid()
			: Shader(SHADER_FRAGMENT)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"solid_color_3d_330.frag");
		}
	}
}