#ifndef FRAME_BUFFER_CONFIG_H
#define FRAME_BUFFER_CONFIG_H

#include "../../../string/string.h"
#include "../../../images/formats.h"

namespace Gpu
{
    class FrameBufferConfig
    {
    public:
        FrameBufferConfig();

        const System::string& Name() const;
        void Name(const System::string& value);

        ImageModule::ImageFormat ColorFormat() const;
        void ColorFormat(ImageModule::ImageFormat value);

        ImageModule::ImageFormat DepthFormat() const;
        void DepthFormat(ImageModule::ImageFormat value);

        int RedBitsCount() const;
        void RedBitsCount(int value);

        int DepthBitsCount() const;
        void DepthBitsCount(int value);

        int DepthSamples() const;
        void DepthSamples(int value);

        int CoverageSamples() const;
        void CoverageSamples(int value);

        unsigned Width() const;
        void Width(unsigned value);

        unsigned Height() const;
        void Height(unsigned value);

    private:
        System::string m_name;
        ImageModule::ImageFormat m_color_format;
        ImageModule::ImageFormat m_depth_format;
        int m_red_bits;
        int m_depth_bits;
        int m_depth_samples;
        int m_coverage_samples;
        unsigned m_width;
        unsigned m_height;
    };
}

#endif // FRAME_BUFFER_CONFIG_H
