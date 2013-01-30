#include "vs_terrain.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderTerrain::VertexShaderTerrain()
			: Shader(SHADER_VERTEX)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.vert");
		}
	}
}