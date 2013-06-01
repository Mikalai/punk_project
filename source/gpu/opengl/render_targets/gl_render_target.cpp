#include "gl_render_target.h"
#include "../error/module.h"
#include "../gl/module.h"

namespace GPU
{
namespace OpenGL
{

RenderTarget::RenderTarget()
    : m_clear_color(0.2, 0.5, 0.8, 1.0)
    , m_viewport(0, 0, 1, 1)
    , m_clear_color_buffer(true)
    , m_clear_depth_buffer(true)
    , m_clear_stencil_buffer(true)
{}

void RenderTarget::SetClearColor(float r, float g, float b, float a)
{
    m_clear_color.Set(r, g, b, a);
    glClearColor(m_clear_color.X(), m_clear_color.Y(), m_clear_color.Z(), m_clear_color.W());
    ValidateOpenGL(L"Unable to set clear color");
}

void RenderTarget::SetClearColor(const Math::vec4 &c)
{
    m_clear_color = c;
    glClearColor(m_clear_color.X(), m_clear_color.Y(), m_clear_color.Z(), m_clear_color.W());
    ValidateOpenGL(L"Unable to set clear color");
}

void RenderTarget::ClearColorBufferEnable(bool value)
{
    m_clear_color_buffer = value;
}

void RenderTarget::ClearDepthBufferEnable(bool value)
{
    m_clear_depth_buffer = value;
}

void RenderTarget::ClearStencilBufferEnable(bool value)
{
    m_clear_stencil_buffer = value;
}

bool RenderTarget::IsClearColorBufferEnabled() const
{
    return m_clear_color_buffer;
}

bool RenderTarget::IsClearDepthBufferEnabled() const
{
    return m_clear_depth_buffer;
}

bool RenderTarget::IsClearStencilBufferEnabled() const
{
    return m_clear_stencil_buffer;
}

void RenderTarget::Clear()
{
    GLbitfield b = 0;

    if (IsClearColorBufferEnabled())
        b |= GL_COLOR_BUFFER_BIT;
    if (IsClearDepthBufferEnabled())
        b |= GL_DEPTH_BUFFER_BIT;
    if (IsClearStencilBufferEnabled())
        b |= GL_STENCIL_BUFFER_BIT;

    glClear(b);
    ValidateOpenGL(L"Unable to clear buffer");
}

void RenderTarget::SetViewport(const Math::Rect& value)
{
    Activate();
    m_viewport = value;
    glViewport((GLsizei)value.GetX(), (GLsizei)value.GetY(), (GLsizei)value.GetWidth(), (GLsizei)value.GetHeight());
    Deactivate();
}

void RenderTarget::Activate()
{
    //	simply unbind all previous buffers
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ValidateOpenGL(L"Can't set clear color");
    Clear();
}

void RenderTarget::Deactivate()
{
    //	simply unbind all previous buffers
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
}

}

}
