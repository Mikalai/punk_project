#ifndef TEXTURE_COMPARE_FUNC_H
#define TEXTURE_COMPARE_FUNC_H

namespace Gpu
{
    enum class TextureCompareFunc { TextureLessEqual,
                                    TextureGreaterEqual,
                                    TextureLess,
                                    TextureGreater,
                                    TextureEqual,
                                    TextureNotEqual,
                                    TextureAlways,
                                    TextureNever };
}

#endif // TEXTURE_COMPARE_FUNC_H
