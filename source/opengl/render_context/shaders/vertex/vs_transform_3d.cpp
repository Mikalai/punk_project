#include "vs_transform_3d.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	ShaderTransform3D::ShaderTransform3D()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"solid_color_3d_330.vert");
	}
}
