#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

namespace GPU
{
namespace OpenGL
{

enum class ShaderType { Bad, Vertex, Fragment, Geometry };

enum class ShaderCollection {
    No,
    VertexBumpMapping,
    FragmentBumpMapping,
    VertexSolidColor,
    FragmentSolidColor,
    VertexSolidVertexColor,
	FragmentSolidVertexColor,
	VertexSolidTextured,
	FragmentSolidTextured,
	VertexLightPerVertexDiffuse,
	FragmentLightPerVertexDiffuse,
	VertexLightPerFragmentDiffuse,
	FragmentLightPerFragmentDiffuse,
	VertexLightPerVertexTextureDiffuse,
	FragmentLightPerVertexTextureDiffuse,
	VertexLightPerFragmentTextureDiffuse,
	FragmentLightPerFragmentTextureDiffuse
};

extern const wchar_t* GetShaderFile(ShaderCollection shader);

}
}
#endif // SHADER_TYPE_H
