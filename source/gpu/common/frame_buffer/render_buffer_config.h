#ifndef RENDERBUFFERCONFIG_H
#define RENDERBUFFERCONFIG_H

#include "../../../string/string.h"
#include "../../../images/formats.h"

namespace Gpu
{
    class RenderBufferConfig
    {
    public:
        RenderBufferConfig();

        void Name(const System::string& value);
        const System::string& Name() const;

        void Format(ImageModule::ImageFormat value);
        ImageModule::ImageFormat Format() const;

        void Bits(int value);
        int Bits() const;

    private:
        System::string m_name;
        ImageModule::ImageFormat m_format;
        int m_bits;
    };
}

#endif // RENDERBUFFERCONFIG_H
