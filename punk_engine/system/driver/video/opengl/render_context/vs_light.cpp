#include "vs_light.h"
#include "../../../../environment.h"

namespace OpenGL
{
	VertexShaderLight::VertexShaderLight()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"per_vertex_lighting_330.vert");
	}
}