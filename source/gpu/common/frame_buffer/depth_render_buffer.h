#ifndef DEPTH_RENDER_BUFFER_H
#define DEPTH_RENDER_BUFFER_H

#include "render_buffer.h"

namespace Gpu
{
    class DepthRenderBuffer : public RenderBuffer
    {
    public:
        DepthRenderBuffer(VideoDriver* driver);
        DepthRenderBuffer(const RenderBuffer&) = delete;
        DepthRenderBuffer& operator = (const DepthRenderBuffer&) = delete;
        virtual ~DepthRenderBuffer();
    };
}

#endif // DEPTH_RENDER_BUFFER_H
