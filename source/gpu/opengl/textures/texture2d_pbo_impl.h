#ifndef _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
#define _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL

#include <memory.h>
#include "../../../images/module.h"
#include "../driver/module.h"
#include "../buffers/module.h"
#include "../error/module.h"
#include "internal_formats.h"
#include "../../common/texture/module.h"
#include "texture_convert.h"

namespace Gpu
{
    namespace OpenGL
    {
        class Texture2DImpl : public Texture2D
        {
        public:
            Texture2DImpl(VideoDriver* driver);
            Texture2DImpl(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, VideoDriver* driver);
            virtual ~Texture2DImpl();
            virtual void Bind() override;
            virtual void Bind(int slot) override;
            virtual void Unbind() override;
            virtual void CopyFromCpu(int x, int y, int width, int height, const void* data) override;
            virtual void Resize(int width, int height) override;
            virtual void Fill(unsigned char data) override;
            virtual int GetHeight() const override;
            virtual int GetWidth() const override;
            virtual void* Map() override;
            virtual void Unmap(void* data) override;
            virtual bool IsValid() const override;
            virtual size_t GetMemoryUsage() const override;
            virtual void SetMinFilter(TextureFilter value) override;
            virtual void SetMagFilter(TextureFilter value) override;
            virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            virtual void SetCompareFunction(TextureCompareFunc value) override;
            virtual void SetCompareMode(TextureCompareMode value) override;
            virtual VideoDriver* GetVideoDriver() override;

            size_t GetPixelSize(GLenum format);
            GLenum GetInternalFormat(GLenum format);
            bool Create(int width, int height, GLenum internal_format, GLenum format, GLenum type, const void* source, bool use_mipmaps);
            void Clear();
            void UpdateMipMaps();
            GLuint GetIndex() const;
        private:
            VideoDriverImpl* m_driver;
            PixelBufferObject* m_pbo;
            GLuint m_texture_id;
            int m_width;
            int m_height;
            int m_pixel_size;
            int m_bind_slot;
            bool m_use_mip_maps;
            GLenum m_format;
            GLenum m_internal_format;
            GLenum m_internal_type;
        };
    }
}

#endif	//	_H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
