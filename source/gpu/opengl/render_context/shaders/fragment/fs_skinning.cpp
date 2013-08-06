#include "fs_skinning.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		FragmentShaderSkinning::FragmentShaderSkinning()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"skinning_330.frag");
		}
	}
}