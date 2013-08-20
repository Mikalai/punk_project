#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstddef>
#include "../../../config.h"
#include "frame_buffer_target.h"

namespace Gpu
{
    class VideoDriver;
    class Texture2D;
    class Texture2DArray;
    class FrameBufferConfig;
    class ColorRenderBuffer;
    class DepthRenderBuffer;

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
        virtual void AttachColorTarget(size_t index, Texture2D* buffer) = 0;
        virtual void AttachColorTarget(size_t index, ColorRenderBuffer* buffer) = 0;
        virtual void AttachDepthTarget(Texture2D* buffer) = 0;
        virtual void AttachDepthTarget(DepthRenderBuffer* buffer) = 0;
        virtual void AttachDepthTarget(Texture2DArray *buffer, size_t index) = 0;
        virtual void SetRenderTarget(FrameBufferTarget value) = 0;
        virtual void SetViewport(int x, int y, int width, int height) = 0;
        virtual void Clear(bool color, bool depth, bool stencil) = 0;
        virtual void SetPolygonOffset(float a, float b) = 0;
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
