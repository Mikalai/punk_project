#include "render_target_back_buffer.h"
#include "../gl/module.h"

namespace Gpu
{
    namespace OpenGL
    {
        RenderTargetBackBuffer::RenderTargetBackBuffer(VideoDriver *driver)
            : RenderTarget(driver)
        {}

        RenderTargetBackBuffer::~RenderTargetBackBuffer()
        {}

        void RenderTargetBackBuffer::Clear(bool color, bool depth, bool stencil)
        {
            auto c = GetClearColor();
            GL_CALL(glClearColor(c.X(), c.Y(), c.Z(), c.W()));
            GL_CALL(glClearDepth(GetClearDepth()));

            GLbitfield b = 0;

            if (color)
                b |= GL_COLOR_BUFFER_BIT;
            if (depth)
                b |= GL_DEPTH_BUFFER_BIT;
            if (stencil)
                b |= GL_STENCIL_BUFFER_BIT;

            GL_CALL(glClear(b));
        }

        void RenderTargetBackBuffer::SetViewport(const Math::Rect &value)
        {
            RenderTarget::SetViewport(value);
            GL_CALL(glViewport((GLsizei)value.GetX(), (GLsizei)value.GetY(), (GLsizei)value.GetWidth(), (GLsizei)value.GetHeight()));
        }

        void RenderTargetBackBuffer::Activate()
        {
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));            
            GL_CALL(glViewport((GLsizei)m_viewport.GetX(), (GLsizei)m_viewport.GetY(), (GLsizei)m_viewport.GetWidth(), (GLsizei)m_viewport.GetHeight()));
        }

        void RenderTargetBackBuffer::Deactivate()
        {
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }
    }
}
