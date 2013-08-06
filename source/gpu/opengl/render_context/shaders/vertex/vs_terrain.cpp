#include "vs_terrain.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		VertexShaderTerrain::VertexShaderTerrain()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.vert");
		}
	}
}