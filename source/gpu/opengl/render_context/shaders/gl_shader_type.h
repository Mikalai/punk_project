#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

#include "../../../../string/string.h"

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
            FragmentSolidTextured2DArray,
            VertexLightPerVertexDiffuse,
            VertexLightPerVertexDiffuseSpecular,
            FragmentLightPerVertexDiffuse,            
            FragmentLightPerVertexDiffuseSpecular,
            VertexLightPerFragmentDiffuse,
            VertexLightPerFragmentDiffuseSpecular,
            FragmentLightPerFragmentDiffuse,
            FragmentLightPerFragmentDiffuseSpecular,
            VertexLightPerVertexTextureDiffuse,
            FragmentLightPerVertexTextureDiffuse,
            VertexLightPerFragmentTextureDiffuse,
            FragmentLightPerFragmentTextureDiffuse,
            VertexSkinningBump,
            VertexSkinningDepth,
            FragmentTextSolidColor,
            FragmentDepth,
            VertexDepth,
            VsPerVertexDiffuseLightingShadowSimple,
            FsPerVertexDiffuseLightingShadowSimple,
            FragmentShadowSingle
        };

        extern const System::string GetShaderFile(ShaderCollection shader);

    }
}
#endif // SHADER_TYPE_H
