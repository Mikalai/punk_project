#ifndef GL_TEXTURE2D_ARRAY_H
#define GL_TEXTURE2D_ARRAY_H

#include "../gl/module.h"
#include "../../common/texture/texture2d_array.h"
#include "../../../images/formats.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VideoDriverImpl;

        class PUNK_ENGINE_LOCAL Texture2DArrayImpl : public Texture2DArray
        {
        public:
            Texture2DArrayImpl(const Texture2DArrayImpl&) = delete;
            Texture2DArrayImpl& operator = (const Texture2DArrayImpl&) = delete;
            Texture2DArrayImpl(int width, int height, int size, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format,
                               ImageModule::DataType type, const void* data, bool use_mipmaps, VideoDriverImpl* driver);
            virtual ~Texture2DArrayImpl();
            virtual bool IsValid() const override;
            virtual size_t GetMemoryUsage() const override;
            virtual void SetMinFilter(TextureFilter value) override;
            virtual void SetMagFilter(TextureFilter value) override;
            virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            virtual void SetCompareFunction(TextureCompareFunc value) override;
            virtual void SetCompareMode(TextureCompareMode value) override;
            virtual void Bind() override;
            virtual void Bind(int slot) override;
            virtual void Unbind() override;
            virtual VideoDriver* GetVideoDriver() override;
            GLuint GetId() const;
        private:

        private:
            VideoDriverImpl* m_video_driver;
            GLuint m_texture_id;
            int m_width;
            int m_height;
            int m_depth;
            int m_slot;
            GLenum m_internal_format;
            GLenum m_format;
            GLenum m_type;
            bool m_use_mip_maps;
        };
    }
}

#endif // GL_TEXTURE2D_ARRAY_H
