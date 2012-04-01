#include "vs_transform_3d.h"
#include "../../../../environment.h"
namespace OpenGL
{
	ShaderTransform3D::ShaderTransform3D()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::GetShaderFolder() + L"solid_color_3d_330.vert");
	}
}
