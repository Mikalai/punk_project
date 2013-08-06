#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

namespace Gpu
{
    namespace OpenGL
    {

        enum class ShaderType { Bad, Vertex, Fragment, Geometry };

        enum class ShaderCollection {
            No,
            VertexBumpMapping,
            VertexBumpMappingShadowMap,
            FragmentBumpMapping,
            FragmentBumpMappingShadowMap,
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
            FragmentLightPerFragmentTextureDiffuse,
            VertexSkinning,
            FragmentTextSolidColor,
            FragmentDepth
        };

        extern const wchar_t* GetShaderFile(ShaderCollection shader);

    }
}
#endif // SHADER_TYPE_H
