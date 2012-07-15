#include "vs_bump.h"
#include "../../../../environment.h"

namespace OpenGL
{
	VertexShaderBump::VertexShaderBump()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"bump_330.vert");
	}
}