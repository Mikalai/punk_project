#include "render_buffer.h"

namespace Gpu
{
    RenderBuffer::RenderBuffer(VideoDriver *driver)
        : m_driver(driver)
    {}

    RenderBuffer::~RenderBuffer()
    {}

    VideoDriver* RenderBuffer::GetVideDriver()
    {
        return m_driver;
    }

    void RenderBuffer::Bind()
    {}

    void RenderBuffer::Unbind()
    {}
}
