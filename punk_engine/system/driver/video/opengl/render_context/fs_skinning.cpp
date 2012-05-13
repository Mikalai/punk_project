#include "fs_skinning.h"
#include "../../../../environment.h"

namespace OpenGL
{
	FragmentVertexSkinning::FragmentVertexSkinning()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"skinning_330.frag");
	}
}