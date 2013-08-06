#ifndef COLOR_RENDER_BUFFER_H
#define COLOR_RENDER_BUFFER_H

#include "render_buffer.h"

namespace Gpu
{
    class ColorRenderBuffer : public RenderBuffer
    {
    public:
        ColorRenderBuffer(VideoDriver* driver);
        ColorRenderBuffer(const ColorRenderBuffer&) = delete;
        ColorRenderBuffer& operator = (ColorRenderBuffer&) = delete;
        virtual ~ColorRenderBuffer();
    };
}

#endif // COLOR_RENDER_BUFFER_H
