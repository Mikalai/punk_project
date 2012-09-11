#include "vs_gui.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	VertexShaderGUI::VertexShaderGUI()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"gui_330.vert");
	}
}