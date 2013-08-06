#include "render_target.h"

namespace Gpu
{

    RenderTarget::RenderTarget(VideoDriver* driver)
        : m_video_driver(driver)
        , m_clear_color(1, 0, 0, 1.0)
        , m_clear_depth(1.0)
        , m_viewport(0, 0, 1, 1)
    {}

    void RenderTarget::SetClearColor(float r, float g, float b, float a)
    {
        m_clear_color.Set(r, g, b, a);
    }

    void RenderTarget::SetClearDepth(float value)
    {
        m_clear_depth = value;
    }

    void RenderTarget::SetClearColor(const Math::vec4 &c)
    {
        m_clear_color = c;
    }

    void RenderTarget::SetViewport(const Math::Rect& value)
    {
        m_viewport = value;
    }

    RenderTarget::~RenderTarget()
    {
    }

    VideoDriver* RenderTarget::GetVideoDriver()
    {
        return m_video_driver;
    }

    const Math::vec4& RenderTarget::GetClearColor() const
    {
        return m_clear_color;
    }

    float RenderTarget::GetClearDepth() const
    {
        return m_clear_depth;
    }
}

