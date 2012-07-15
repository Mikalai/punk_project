#include "vs_terrain.h"
#include "../../../../environment.h"

namespace OpenGL
{
	ShaderTerrainVertex::ShaderTerrainVertex()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.vert");
	}
}
