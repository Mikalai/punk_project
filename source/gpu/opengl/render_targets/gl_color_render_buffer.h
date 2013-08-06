#ifndef GL_COLOR_RENDER_BUFFER_H
#define GL_COLOR_RENDER_BUFFER_H

#include "../gl/module.h"
#include "../../common/frame_buffer/color_render_buffer.h"

namespace Gpu
{
    class FrameBufferConfig;

    namespace OpenGL
    {
        class OpenGLColorRenderBuffer : public ColorRenderBuffer
        {
        public:
            /**
             * @brief OpenGLColorRenderBuffer create an opengl color buffer, compatible with
             * frame buffer with current config
             * @param driver
             */
            OpenGLColorRenderBuffer(FrameBufferConfig* config, VideoDriver* driver);
            virtual ~OpenGLColorRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index();
        private:
            GLuint m_buffer;
        };
    }
}

#endif // GL_COLOR_RENDER_BUFFER_H
