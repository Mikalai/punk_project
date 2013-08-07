#ifndef _H_PUNK_GPU_TEXTURE_2D
#define _H_PUNK_GPU_TEXTURE_2D

#include <iosfwd>
#include "../../../system/object.h"
#include "../../gpu_config.h"
#include "../../../images/formats.h"
#include "texture.h"

namespace System { class string; }

namespace ImageModule
{
	class Image;
}

namespace Gpu
{
    class VideoDriver;

    class PUNK_ENGINE_API Texture2D : public Texture
	{
    public:
        using Texture::Bind;

    public:
        Texture2D() = default;
        virtual ~Texture2D();        
        virtual void Bind(int slot) = 0;        
        virtual void CopyFromCpu(int x, int y, int width, int height, const void* data) = 0;
        virtual void Resize(int width, int height) = 0;
        virtual void Fill(unsigned char data) = 0;
        virtual int GetHeight() const = 0;
        virtual int GetWidth() const = 0;
        virtual void* Map() = 0;
        virtual void Unmap(void* data) = 0;

    private:
        Texture2D(const Texture2D& texture) = delete;
        Texture2D& operator = (const Texture2D& texture) = delete;

        friend class VideoDriver;
    };
}

#endif	//	_H_PUNK_GPU_TEXTURE_2D
