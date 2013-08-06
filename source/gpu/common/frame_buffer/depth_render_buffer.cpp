#include "depth_render_buffer.h"

namespace Gpu
{
    DepthRenderBuffer::DepthRenderBuffer(VideoDriver *driver)
        : RenderBuffer(driver)
    {}

    DepthRenderBuffer::~DepthRenderBuffer()
    {}
}
