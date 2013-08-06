#include "frame_buffer.h"
#include "frame_buffer_config.h"
#include "../texture/module.h"

namespace Gpu
{
    FrameBuffer::FrameBuffer(VideoDriver *driver)
        : m_config{nullptr}
        , m_driver{driver}
        , m_color_texture{nullptr}
        , m_depth_texture{nullptr}
    {
    }

    FrameBuffer::~FrameBuffer()
    {
        delete m_color_texture;
        m_color_texture = nullptr;
        delete m_depth_texture;
        m_depth_texture = nullptr;
        delete m_config;
        m_config = nullptr;
    }

    Texture2D* FrameBuffer::GetColorTexture()
    {
        return m_color_texture;
    }

    Texture2D* FrameBuffer::GetDepthTexture()
    {
        return m_depth_texture;
    }

    void FrameBuffer::Bind()
    {
    }

    void FrameBuffer::Unbind()
    {
    }

    VideoDriver* FrameBuffer::GetVideoDriver()
    {
        return m_driver;
    }

    FrameBufferConfig* FrameBuffer::Config() const
    {
        return m_config;
    }

    void FrameBuffer::Config(FrameBufferConfig *config)
    {
        if (m_config)
            delete m_config;
        m_config = new FrameBufferConfig(*config);
    }
}
