#ifndef RENDER_BUFFER_H
#define RENDER_BUFFER_H

#include "../../../config.h"

namespace Gpu
{
    class VideoDriver;

    class PUNK_ENGINE_API RenderBuffer
    {
    public:
        RenderBuffer(VideoDriver* driver);
        RenderBuffer(const RenderBuffer&) = delete;
        RenderBuffer& operator = (const RenderBuffer&) = delete;
        virtual ~RenderBuffer();
        VideoDriver* GetVideDriver();

        virtual void Bind();
        virtual void Unbind();

    private:
        VideoDriver* m_driver;
    };
}

#endif // RENDER_BUFFER_H
