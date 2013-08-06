#include "vs_painter.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		VertexShaderPainter::VertexShaderPainter()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"painter_330.vert");
		}
	}
}