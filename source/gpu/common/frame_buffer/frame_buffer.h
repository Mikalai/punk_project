#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../../../config.h"

namespace Gpu
{
    class VideoDriver;
    class Texture2D;
    class FrameBufferConfig;

    class PUNK_ENGINE_API FrameBuffer
    {
    public:
        FrameBuffer(VideoDriver* driver);
        FrameBuffer(const FrameBuffer&) = delete;
        FrameBuffer& operator = (const FrameBuffer&) = delete;
        virtual ~FrameBuffer();
        virtual void Bind();
        virtual void Unbind();
        virtual void Config(FrameBufferConfig *config);

        VideoDriver* GetVideoDriver();        

        Texture2D* GetColorTexture();
        Texture2D* GetDepthTexture();      

        FrameBufferConfig* Config() const;


    protected:
        FrameBufferConfig* m_config;
        Texture2D* m_color_texture;
        Texture2D* m_depth_texture;
        VideoDriver* m_driver;
    };
}

#endif // FRAMEBUFFER_H
