#ifndef GL_FRAMEBUFFERIMPL_H
#define GL_FRAMEBUFFERIMPL_H

#include "../gl/module.h"
#include "../../common/frame_buffer/frame_buffer.h"
#include "gl_color_render_buffer.h"
#include "gl_depth_render_buffer.h"

namespace Gpu
{
    class FrameBufferConfig;

    namespace OpenGL
    {
        class OpenGLFrameBuffer : public FrameBuffer
        {
        public:
            using FrameBuffer::Config;

        public:
            OpenGLFrameBuffer(VideoDriver *driver);
            virtual ~OpenGLFrameBuffer();
            virtual void Bind() override;
            virtual void Unbind() override;
            virtual void Config(FrameBufferConfig *config) override;

            virtual void AttachColorTarget(size_t index, Texture2D* buffer) override;
            virtual void AttachColorTarget(size_t index, ColorRenderBuffer* buffer) override;
            virtual void AttachDepthTarget(Texture2D* buffer) override;
            virtual void AttachDepthTarget(DepthRenderBuffer* buffer) override;
            virtual void AttachDepthTarget(Texture2DArray *buffer, size_t index) override;
            virtual void SetRenderTarget(FrameBufferTarget value) override;
            virtual void SetViewport(int x, int y, int width, int height) override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual void SetPolygonOffset(float a, float b) override;

        private:
            void Clear();
            void CheckConfigCompatibility();
            void Check();
        private:
            OpenGLColorRenderBuffer* m_color_rb;
            OpenGLDepthRenderBuffer* m_depth_rb;
            OpenGLFrameBuffer* m_resolve_rb;
            GLuint m_fb;
            GLuint m_prev_fb;
        };
    }
}

#endif // GL_FRAMEBUFFERIMPL_H
