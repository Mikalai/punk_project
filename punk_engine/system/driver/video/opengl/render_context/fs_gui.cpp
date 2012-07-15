#include "fs_gui.h"
#include "../../../../environment.h"

namespace OpenGL
{
	FragmentShaderGUI::FragmentShaderGUI()
		: Shader(SHADER_FRAGMENT)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"gui_330.frag");
	}
}