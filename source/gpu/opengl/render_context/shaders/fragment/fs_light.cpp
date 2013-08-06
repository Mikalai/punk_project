#include "fs_light.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		FragmentShaderLight::FragmentShaderLight()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"per_vertex_lighting_330.frag");
		}
	}
}
