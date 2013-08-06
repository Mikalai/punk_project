#include "color_render_buffer.h"

namespace Gpu
{
    ColorRenderBuffer::ColorRenderBuffer(VideoDriver *driver)
        : RenderBuffer(driver)
    {}

    ColorRenderBuffer::~ColorRenderBuffer()
    {}
}
