#include "vs_transformed_textured_3d.h"
#include "../../../../system/environment.h"

namespace OpenGL
{
	VertexShaderTransformTextured3D::VertexShaderTransformTextured3D()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"textured_2d_330.vert");
	}
}
