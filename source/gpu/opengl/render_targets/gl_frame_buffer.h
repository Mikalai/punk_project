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

            void AttachColorTarget(size_t index, Texture2D* buffer);
            void AttachColorTarget(size_t index, OpenGLColorRenderBuffer* buffer);
            void AttachDepthTarget(Texture2D* buffer);
            void AttachDepthTarget(OpenGLDepthRenderBuffer* buffer);

        private:
            void Clear();
            void CheckConfigCompatibility();
            void Check();
        private:
            OpenGLColorRenderBuffer* m_color_rb;
            OpenGLDepthRenderBuffer* m_depth_rb;
            OpenGLFrameBuffer* m_resolve_rb;
            GLuint m_fb;
        };
    }
}

#endif // GL_FRAMEBUFFERIMPL_H
