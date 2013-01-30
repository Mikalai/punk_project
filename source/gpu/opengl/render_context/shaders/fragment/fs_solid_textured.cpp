#include "fs_solid_textured.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderSolidTextured::FragmentShaderSolidTextured()
			: Shader(SHADER_FRAGMENT)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"textured_2d_330.frag");
		}
	}
}