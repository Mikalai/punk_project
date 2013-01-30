#include "vs_solid_color.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderSolid::VertexShaderSolid()
			: Shader(SHADER_VERTEX)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"solid_color_3d_330.vert");
		}
	}
}