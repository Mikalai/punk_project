#ifndef _H_PUNK_GPU_TEXTURE_2D
#define _H_PUNK_GPU_TEXTURE_2D

#include <iosfwd>
#include "../../../system/object.h"
#include "../../gpu_config.h"
#include "../../../images/formats.h"
#include "texture_filter.h"
#include "texture_wrap.h"
#include "texture_compare_func.h"
#include "texture_compare_mode.h"

namespace System { class string; }

namespace ImageModule
{
	class Image;
}

namespace Gpu
{
    class VideoDriver;

    class PUNK_ENGINE_API Texture2D
	{
    public:
        Texture2D() = default;
        virtual ~Texture2D();
        virtual void Bind() = 0;
        virtual void Bind(int slot) = 0;
        virtual void Unbind() = 0;
        virtual void CopyFromCpu(int x, int y, int width, int height, const void* data) = 0;
        virtual void Resize(int width, int height) = 0;
        virtual void Fill(unsigned char data) = 0;
        virtual int GetHeight() const = 0;
        virtual int GetWidth() const = 0;
        virtual void* Map() = 0;
        virtual void Unmap(void* data) = 0;
        virtual bool IsValid() const = 0;
        virtual size_t GetMemoryUsage() const = 0;
        virtual void SetMinFilter(TextureFilter value) = 0;
        virtual void SetMagFilter(TextureFilter value) = 0;
        virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) = 0;
        virtual void SetCompareFunction(TextureCompareFunc value) = 0;
        virtual void SetCompareMode(TextureCompareMode value) = 0;

    private:
        Texture2D(const Texture2D& texture) = delete;
        Texture2D& operator = (const Texture2D& texture) = delete;

        friend class VideoDriver;
    };
}

#endif	//	_H_PUNK_GPU_TEXTURE_2D
