#include "vs_grass.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		VertexShaderGrass::VertexShaderGrass()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"grass_330.vert");
		}
	}
}