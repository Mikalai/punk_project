#include "vs_transform_3d.h"
#include "../../../../../system/environment.h"

namespace Gpu
{
	namespace OpenGL
	{
		ShaderTransform3D::ShaderTransform3D()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"solid_color_3d_330.vert");
		}
	}
}