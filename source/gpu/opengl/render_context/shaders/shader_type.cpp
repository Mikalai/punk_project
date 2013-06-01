#include <utility>
#include "shader_type.h"
#include "../../../../system/errors/module.h"

namespace GPU
{
namespace OpenGL
{

typedef std::pair<ShaderCollection, const wchar_t*> ShaderFile;

static const ShaderFile g_shaders[] = {
    ShaderFile(ShaderCollection::No, L""),
    ShaderFile(ShaderCollection::VertexSolidColor, L"solid_color_3d_330.vert"),
    ShaderFile(ShaderCollection::FragmentSolidColor, L"solid_color_3d_330.frag"),
	ShaderFile(ShaderCollection::VertexSolidVertexColor, L"solid_vertex_color.vert"),
	ShaderFile(ShaderCollection::FragmentSolidVertexColor, L"solid_vertex_color.frag"),
	ShaderFile(ShaderCollection::VertexSolidTextured, L"solid_textured_330.vert"),
	ShaderFile(ShaderCollection::FragmentSolidTextured, L"solid_textured_330.frag"),
	ShaderFile(ShaderCollection::VertexLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.vert"),
	ShaderFile(ShaderCollection::FragmentLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.frag"),
	ShaderFile(ShaderCollection::VertexLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.vert"),
	ShaderFile(ShaderCollection::FragmentLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.frag"),
	ShaderFile(ShaderCollection::VertexLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.vert"),
	ShaderFile(ShaderCollection::FragmentLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.frag"),
	ShaderFile(ShaderCollection::VertexLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.vert"),
	ShaderFile(ShaderCollection::FragmentLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.frag"),
    ShaderFile(ShaderCollection::No, L"")
};

const wchar_t* GetShaderFile(ShaderCollection shader)
{
    const wchar_t* error = L"";
    for (auto it : g_shaders)
    {
        if (it.first == shader)
            return it.second;
    }
	throw System::PunkInvalidArgumentException(System::string(L"Shader not found"));
}


}
}
