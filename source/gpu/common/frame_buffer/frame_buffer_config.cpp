#include "frame_buffer_config.h"

namespace Gpu
{
    FrameBufferConfig::FrameBufferConfig()
        : m_width(256)
        , m_height(256)
    {
    }

    const System::string& FrameBufferConfig::Name() const
    {
        return m_name;
    }

    void FrameBufferConfig::Name(const System::string& value)
    {
        m_name = value;
    }

    ImageModule::ImageFormat FrameBufferConfig::ColorFormat() const
    {
        return m_color_format;
    }

    void FrameBufferConfig::ColorFormat(ImageModule::ImageFormat value)
    {
        m_color_format = value;
    }

    ImageModule::ImageFormat FrameBufferConfig::DepthFormat() const
    {
        return m_depth_format;
    }

    void FrameBufferConfig::DepthFormat(ImageModule::ImageFormat value)
    {
        m_depth_format = value;
    }

    int FrameBufferConfig::RedBitsCount() const
    {
        return m_red_bits;
    }

    void FrameBufferConfig::RedBitsCount(int value)
    {
        m_red_bits = value;
    }

    int FrameBufferConfig::DepthBitsCount() const
    {
        return m_depth_bits;
    }

    void FrameBufferConfig::DepthBitsCount(int value)
    {
        m_depth_bits = value;
    }

    int FrameBufferConfig::DepthSamples() const
    {
        return m_depth_samples;
    }

    void FrameBufferConfig::DepthSamples(int value)
    {
        m_depth_samples = value;
    }

    int FrameBufferConfig::CoverageSamples() const
    {
        return m_coverage_samples;
    }

    void FrameBufferConfig::CoverageSamples(int value)
    {
        m_coverage_samples = value;
    }

    unsigned FrameBufferConfig::Width() const
    {
        return m_width;
    }

    void FrameBufferConfig::Width(unsigned value)
    {
        m_width = value;
    }

    unsigned FrameBufferConfig::Height() const
    {
        return m_height;
    }

    void FrameBufferConfig::Height(unsigned value)
    {
        m_height = value;
    }
}
