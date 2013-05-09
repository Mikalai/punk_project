#include "fs_solid_textured.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		FragmentShaderSolidTextured::FragmentShaderSolidTextured()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"textured_2d_330.frag");
		}
	}
}