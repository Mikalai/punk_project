#ifndef SHADER_VAR_TABLE_H
#define SHADER_VAR_TABLE_H

namespace Gpu
{
    enum class ShaderVarTable {
        VertexWorldPosition,
        VertexViewWorldPosition,
        VertexProjectionViewWorldPosition,
        VertexWorldNormal,
        VertexViewWorldNormal,
        VertexTextureCoordinate0,
        VertexTextureCoordinate1,
        VertexTextureCoordinate2,
        VertexTextureCoordinate3,
        ViewDirection,
        LightDirection,
        LightPosition,
        FragmentColor,
        DiffuseColor,

    };
}

#endif // SHADER_VAR_TABLE_H
