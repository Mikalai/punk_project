#include <utility>
#include "gl_shader_type.h"
#include "../../../../system/errors/module.h"

namespace Gpu
{
    namespace OpenGL
    {

        typedef std::pair<ShaderCollection, const wchar_t*> ShaderFile;

        static const ShaderFile g_shaders[] = {
            ShaderFile(ShaderCollection::No, L""),
            ShaderFile(ShaderCollection::VertexBumpMapping, L"bump_330.vert"),
            ShaderFile(ShaderCollection::VertexBumpMappingShadowMap, L"bump_330_shadow_map.vert"),
            ShaderFile(ShaderCollection::FragmentBumpMapping, L"bump_330.frag"),
            ShaderFile(ShaderCollection::FragmentBumpMappingShadowMap, L"bump_330_shadow_map.frag"),
            ShaderFile(ShaderCollection::VertexSolidColor, L"solid_color_3d_330.vert"),
            ShaderFile(ShaderCollection::FragmentSolidColor, L"solid_color_3d_330.frag"),
            ShaderFile(ShaderCollection::VertexSolidVertexColor, L"solid_vertex_color.vert"),
            ShaderFile(ShaderCollection::FragmentSolidVertexColor, L"solid_vertex_color.frag"),
            ShaderFile(ShaderCollection::VertexSolidTextured, L"solid_textured_330.vert"),
            ShaderFile(ShaderCollection::FragmentSolidTextured, L"solid_textured_330.frag"),
            ShaderFile(ShaderCollection::FragmentSolidTextured2DArray, L"solid_texture_2d_array.frag"),
            ShaderFile(ShaderCollection::VertexLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.vert"),
            ShaderFile(ShaderCollection::FragmentLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.frag"),
            ShaderFile(ShaderCollection::VertexLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.vert"),
            ShaderFile(ShaderCollection::FragmentLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.frag"),
            ShaderFile(ShaderCollection::VertexLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.vert"),
            ShaderFile(ShaderCollection::FragmentLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.frag"),
            ShaderFile(ShaderCollection::VertexLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.vert"),
            ShaderFile(ShaderCollection::FragmentLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.frag"),
            ShaderFile(ShaderCollection::VertexSkinningBump, L"skinning_bump_330.vert"),
            ShaderFile(ShaderCollection::VertexSkinningDepth, L"skinning_depth_330.vert"),
            ShaderFile(ShaderCollection::FragmentTextSolidColor, L"text_color_330.frag"),
            ShaderFile(ShaderCollection::FragmentDepth, L"depth.frag"),
            ShaderFile(ShaderCollection::VertexDepth, L"depth.vert"),
            ShaderFile(ShaderCollection::VertexShadow, L"shadow.vert"),
            ShaderFile(ShaderCollection::FragmentShadowSingle, L"shadow_single.frag"),
            ShaderFile(ShaderCollection::No, L"")
        };

        const System::string GetShaderFile(ShaderCollection shader)
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
