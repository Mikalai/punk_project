#ifndef TEXTURE_WRAP_H
#define TEXTURE_WRAP_H

namespace Gpu
{
    enum class TextureWrapDirection { S, T, R };
    enum class TextureWrapMode { ClampToEdge, ClampToBorder, MirroredRepeat, Repeat, MirrorClampToEdge };
}

#endif // TEXTURE_WRAP_H
