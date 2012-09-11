#include "vs_bump.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	VertexShaderBump::VertexShaderBump()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"bump_330.vert");
	}
}