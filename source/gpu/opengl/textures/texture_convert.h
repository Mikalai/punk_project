#ifndef TEXTURE_CONVER_H
#define TEXTURE_CONVER_H

#include "../gl/module.h"

namespace ImageModule
{
    enum ImageFormat : unsigned;
}

namespace Gpu
{
    enum class TextureFilter;
    enum class TextureWrapMode;
    enum class TextureWrapDirection;
    enum class TextureCompareFunc;
    enum class TextureCompareMode;

    namespace OpenGL
    {
        GLenum Convert(const TextureFilter& value);
        GLenum Convert(const TextureWrapMode& value);
        GLenum Convert(const TextureWrapDirection& value);
        GLenum Convert(const TextureCompareFunc& value);
        GLenum Convert(const TextureCompareMode& value);
        GLenum Convert(const ImageModule::ImageFormat& format);
    }
}

#endif // TEXTURE_CONVER_H
