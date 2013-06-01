#ifndef _H_PUNK_GPU_OPENGL_RENDER_TARGET
#define _H_PUNK_GPU_OPENGL_RENDER_TARGET

#include "../../common/render_target.h"

namespace GPU
{
namespace OpenGL
{

class PUNK_ENGINE_PUBLIC RenderTarget
{
public:
    RenderTarget();

    void SetClearColor(float r, float g, float b, float a);
    void SetClearColor(const Math::vec4& c);


    virtual void SetViewport(const Math::Rect& value);
    virtual void Activate();
    virtual void Deactivate();
    virtual void Clear();
    virtual ~RenderTarget();

    void ClearColorBufferEnable(bool value);
    void ClearDepthBufferEnable(bool value);
    void ClearStencilBufferEnable(bool value);

    bool IsClearColorBufferEnabled() const;
    bool IsClearDepthBufferEnabled() const;
    bool IsClearStencilBufferEnabled() const;

private:
    Math::vec4 m_clear_color;
    Math::Rect m_viewport;
    bool m_clear_color_buffer;
    bool m_clear_depth_buffer;
    bool m_clear_stencil_buffer;    

private:
    RenderTarget(const RenderTarget&) = delete;
    RenderTarget& operator = (const RenderTarget&) = delete;
};

}
}

#endif	//	_H_PUNK_GPU_OPENGL_RENDER_TARGET
