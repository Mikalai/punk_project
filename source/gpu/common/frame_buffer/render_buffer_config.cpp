#include "render_buffer_config.h"

namespace Gpu
{
    RenderBufferConfig::RenderBufferConfig()
    {
    }

    void RenderBufferConfig::Name(const System::string& value)
    {
        m_name = value;
    }

    const System::string& RenderBufferConfig::Name() const
    {
        return m_name;
    }

    void RenderBufferConfig::Format(ImageModule::ImageFormat value)
    {
        m_format = value;
    }

    ImageModule::ImageFormat RenderBufferConfig::Format() const
    {
        return m_format;
    }

    void RenderBufferConfig::Bits(int value)
    {
        m_bits = value;
    }

    int RenderBufferConfig::Bits() const
    {
        return m_bits;
    }
}
