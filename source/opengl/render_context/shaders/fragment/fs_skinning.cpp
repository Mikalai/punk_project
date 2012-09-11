#include "fs_skinning.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	FragmentShaderSkinning::FragmentShaderSkinning()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"skinning_330.frag");
	}
}