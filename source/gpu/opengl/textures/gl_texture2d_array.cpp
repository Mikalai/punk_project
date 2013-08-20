#include "gl_texture2d_array.h"
#include "texture_convert.h"
#include "../../common/texture/module.h"
#include "../driver/module.h"

namespace Gpu
{
    namespace OpenGL
    {
        Texture2DArrayImpl::Texture2DArrayImpl(int width, int height, int size, ImageModule::ImageFormat internal_format,
                                               ImageModule::ImageFormat format, ImageModule::DataType type, const void *data,
                                               bool use_mipmaps, VideoDriverImpl *driver)
            : m_video_driver(driver)
            , m_width(width)
            , m_height(height)
            , m_depth(size)
            , m_internal_format(Convert(internal_format))
            , m_format(Convert(format))
            , m_type(Convert(type))
            , m_use_mip_maps(use_mipmaps)
            , m_texture_id(0)
            , m_slot(0)
        {
            GL_CALL(glGenTextures(1, &m_texture_id));
            Bind();
            GL_CALL(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, m_internal_format, m_width, m_height, m_depth, 0, m_format, m_type, data));
            Unbind();
        }

        Texture2DArrayImpl::~Texture2DArrayImpl()
        {
            GL_CALL(glDeleteTextures(1, &m_texture_id));
            m_texture_id = 0;
        }

        bool Texture2DArrayImpl::IsValid() const
        {
            return m_texture_id != 0;
        }

        size_t Texture2DArrayImpl::GetMemoryUsage() const
        {
            return m_width * m_height * m_depth * 4;    //  TODO: Should be something better
        }

        void Texture2DArrayImpl::SetMinFilter(TextureFilter value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, Convert(value)));
            Unbind();
        }

        void Texture2DArrayImpl::SetMagFilter(TextureFilter value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, Convert(value)));
            Unbind();
        }

        void Texture2DArrayImpl::SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, Convert(dir), Convert(mode)));
            Unbind();
        }

        void Texture2DArrayImpl::SetCompareFunction(TextureCompareFunc value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, Convert(value)));
            Unbind();
        }

        void Texture2DArrayImpl::SetCompareMode(TextureCompareMode value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, Convert(value)));
            Unbind();
        }

        void Texture2DArrayImpl::Bind()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture_id));
        }

        void Texture2DArrayImpl::Bind(int slot)
        {
            m_slot = slot;
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
            Bind();
        }

        void Texture2DArrayImpl::Unbind()
        {
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
        }

        VideoDriver* Texture2DArrayImpl::GetVideoDriver()
        {
            return m_video_driver;
        }

        GLuint Texture2DArrayImpl::GetId() const
        {
            return m_texture_id;
        }
    }
}
