#ifndef TEXTURE2D_ARRAY_H
#define TEXTURE2D_ARRAY_H

#include "texture.h"

namespace Gpu
{
    class Texture2DArray : public Texture
    {
    public:
        Texture2DArray() = default;
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

#endif // TEXTURE2D_ARRAY_H
