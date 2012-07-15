#include "vs_transformed_textured_3d.h"
#include "../../../../environment.h"
namespace OpenGL
{
	ShaderTransformTextured3D::ShaderTransformTextured3D()
		: Shader(SHADER_VERTEX)
	{
		CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"textured_2d_330.vert");
	}
}
