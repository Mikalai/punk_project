#include "vs_gui.h"
#include "../../../../environment.h"

namespace OpenGL
{
	VertexShaderGUI::VertexShaderGUI()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"gui_330.vert");
	}
}