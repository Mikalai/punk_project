#include "texture2d_pbo_impl.h"

namespace Gpu
{
    namespace OpenGL
    {
        Texture2DImpl::Texture2DImpl(VideoDriver* driver)
            : m_driver(dynamic_cast<VideoDriverImpl*>(driver))
            , m_texture_id(0)
            , m_bind_slot(0)
            , m_use_mip_maps(false)
            , m_width(0)
            , m_height(0)
            , m_format(0)
            , m_pbo(nullptr)
        {
            //Create(64, 64, GL_RED, 0);
        }

        Texture2DImpl::Texture2DImpl(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, VideoDriver* driver)
            : m_driver(dynamic_cast<VideoDriverImpl*>(driver))
            , m_pbo(nullptr)
        {
            Create(width, height, ImageFormatToOpenGL(internal_format), ImageFormatToOpenGL(format), ImageDataTypeToOpenGL(type), data, use_mipmaps);
        }

        Texture2DImpl::~Texture2DImpl()
        {
            Clear();
        }

        size_t Texture2DImpl::GetMemoryUsage() const
        {
            return m_pbo->GetSize();
        }

        void Texture2DImpl::Bind()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void Texture2DImpl::Bind(int slot)
        {
            m_bind_slot = slot;
            GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void Texture2DImpl::Unbind()
        {
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_bind_slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
        }

        void Texture2DImpl::Clear()
        {
            m_driver->GetVideoMemory()->FreePixelBuffer(m_pbo);

            if (m_texture_id)
            {
                glDeleteTextures(1, &m_texture_id);
                ValidateOpenGL(L"Can't delete texture");
                m_texture_id = 0;
            }
        }

        void Texture2DImpl::CopyFromCpu(int x, int y, int width, int height, const void* data)
        {
            if (x < 0)
                throw System::PunkException("Bad parameter");
            if (y < 0)
                throw System::PunkException("Bad parameter");
            if (x + width > m_width)
                throw System::PunkException("Bad parameter");
            if (y + height > m_height)
                throw System::PunkException("Bad parameter");


            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, m_format, m_internal_type, data));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));


            if (m_use_mip_maps)
            {
                GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
                GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
                GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
            }
        }

        void Texture2DImpl::Resize(int width, int height)
        {
            if (m_texture_id != 0)
            {
                GL_CALL(glDeleteTextures(1, &m_texture_id));
            }

            m_width = width;
            m_height = height;
            GL_CALL(glGenTextures(1, &m_texture_id));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_internal_format, m_internal_type, 0));
            Fill(0);
        }

        size_t Texture2DImpl::GetPixelSize(GLenum format)
        {
            switch(format)
            {
            case GL_RED:
                return 1;
            case GL_RGB:
                return 3;
            case GL_RGBA:
            case GL_RGBA8:
            case GL_R32F:
                return 4;
            case GL_DEPTH_COMPONENT16:
                return 2;
            case GL_DEPTH_COMPONENT24:
                return 3;
            case GL_DEPTH_COMPONENT32:
                return 4;
            default:
                return 0;
            }
        }

        GLenum Texture2DImpl::GetInternalFormat(GLenum format)
        {
            switch(format)
            {
            case GL_RED:
            case GL_ALPHA:
            case GL_R32F:
                return GL_RED;
            case GL_RGB:
                return GL_RGB;
            case GL_RGBA:
                return GL_RGBA;
            case GL_DEPTH_COMPONENT16:
            case GL_DEPTH_COMPONENT24:
            case GL_DEPTH_COMPONENT32:
                return GL_DEPTH_COMPONENT;
            default:
                throw System::PunkException(L"Can't find suitable internal format");
            }
        }

        bool Texture2DImpl::Create(int width, int height, GLenum internal_format, GLenum format, GLenum type, const void* source, bool use_mipmaps)
        {
            m_width = width;
            m_height = height;
            m_internal_format = internal_format;
            m_format = format;
            m_use_mip_maps = use_mipmaps;
            m_pixel_size = GetPixelSize(internal_format);
            m_internal_type = type;

            GL_CALL(glGenTextures(1, &m_texture_id));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));

            if (use_mipmaps)
            {
                GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            }
            else
            {
                GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            }

            GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT));

            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, 0));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

            //	if data available than copy them
            if (source)
            {
                void* data = Map();
                if (data)
                {
                    memcpy(data, source, m_width * m_height * m_pixel_size);
                    Unmap(0);
                }
            }
            if (m_use_mip_maps)
                UpdateMipMaps();

            return true;
        }

        void Texture2DImpl::UpdateMipMaps()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
        }

        void* Texture2DImpl::Map()
        {
            if (m_pbo)
                throw System::PunkException(L"Texture already mapped");
            m_pbo = m_driver->GetVideoMemory()->AllocatePixelBuffer(m_width*m_height*m_pixel_size);
            void* ptr = m_pbo->Map();
            if (!ptr)
                m_driver->GetVideoMemory()->FreePixelBuffer(m_pbo);
            return ptr;
        }

        void Texture2DImpl::Unmap(void*)
        {
            if (!m_pbo)
                throw System::PunkException("Texture was not mapped");
            m_pbo->Unmap();
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            m_pbo->Bind();
            GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_internal_format, m_internal_type, 0));
            m_pbo->Unbind();
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

            m_driver->GetVideoMemory()->FreePixelBuffer(m_pbo);
            m_pbo = nullptr;

            if (m_use_mip_maps)
                UpdateMipMaps();
        }

        void Texture2DImpl::Fill(unsigned char byte)
        {
            void* dst = Map();
            if (dst)
            {
                memset(dst, byte, m_width*m_height*m_pixel_size);
                Unmap(dst);

                if (m_use_mip_maps)
                    UpdateMipMaps();
            }
        }

        void Texture2DImpl::SetMinFilter(TextureFilter value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Convert(value)));
            Unbind();
        }

        void Texture2DImpl::SetMagFilter(TextureFilter value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Convert(value)));
            Unbind();
        }

        void Texture2DImpl::SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, Convert(dir), Convert(mode)));
            Unbind();
        }

        void Texture2DImpl::SetCompareFunction(TextureCompareFunc value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, Convert(value)));
            Unbind();
        }

        void Texture2DImpl::SetCompareMode(TextureCompareMode value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, Convert(value)));
            Unbind();
        }

        int Texture2DImpl::GetHeight() const
        {
            return m_width;
        }

        int Texture2DImpl::GetWidth() const
        {
            return m_height;
        }

        GLuint Texture2DImpl::GetIndex() const
        {
            return m_texture_id;
        }

        bool Texture2DImpl::IsValid() const
        {
            return m_texture_id != 0;
        }

        VideoDriver* Texture2DImpl::GetVideoDriver()
        {
            return m_driver;
        }
    }
}

