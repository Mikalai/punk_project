#ifndef PUNK_OPENGL_DEPTH_BUFFER_H
#define PUNK_OPENGL_DEPTH_BUFFER_H

#include "../gl/module.h"
#include "../../common/frame_buffer/depth_render_buffer.h"

namespace Gpu
{
    class FrameBufferConfig;

    namespace OpenGL
    {
        class OpenGLDepthRenderBuffer : public DepthRenderBuffer
        {
        public:

            OpenGLDepthRenderBuffer(FrameBufferConfig* config, VideoDriver* driver);
            virtual ~OpenGLDepthRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index() const;

        private:
            GLuint m_buffer;
        };
    }
}

#endif // PUNK_OPENGL_GL_DEPTH_BUFFER_H
