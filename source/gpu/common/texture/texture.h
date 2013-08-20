#ifndef TEXTURE_H
#define TEXTURE_H

#include "texture_filter.h"
#include "texture_wrap.h"
#include "texture_compare_func.h"
#include "texture_compare_mode.h"
#include <cstddef>

namespace Gpu
{
    class VideoDriver;

    class Texture
    {
    public:
        virtual bool IsValid() const = 0;
        virtual size_t GetMemoryUsage() const = 0;
        virtual void SetMinFilter(TextureFilter value) = 0;
        virtual void SetMagFilter(TextureFilter value) = 0;
        virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) = 0;
        virtual void SetCompareFunction(TextureCompareFunc value) = 0;
        virtual void SetCompareMode(TextureCompareMode value) = 0;
        virtual void Bind() = 0;
        virtual void Bind(int slot) = 0;
        virtual void Unbind() = 0;
        virtual VideoDriver* GetVideoDriver() = 0;
    };
}

#endif // TEXTURE_H
