#include "vs_transformed_textured_3d.h"
#include "../../../../../system/environment.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexShaderTransformTextured3D::VertexShaderTransformTextured3D()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"textured_2d_330.vert");
		}
	}
}