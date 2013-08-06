#ifndef _H_PUNK_GPU_RENDER_TARGET
#define _H_PUNK_GPU_RENDER_TARGET

#include "../../config.h"
#include "../../math/vec4.h"
#include "../../math/mat4.h"
#include "../../math/rect.h"

namespace Gpu
{
    class VideoDriver;

    class PUNK_ENGINE_API RenderTarget
    {
    public:
        RenderTarget(VideoDriver* driver);

        void SetClearColor(float r, float g, float b, float a);
        void SetClearColor(const Math::vec4& c);
        void SetClearDepth(float value);


        virtual void SetViewport(const Math::Rect& value) = 0;
        virtual void Activate() = 0;
        virtual void Deactivate() = 0;
        virtual void Clear(bool color, bool depth, bool stencil) = 0;
        virtual ~RenderTarget();

        VideoDriver* GetVideoDriver();

        const Math::vec4& GetClearColor() const;
        float GetClearDepth() const;

    protected:
        Math::vec4 m_clear_color;
        Math::Rect m_viewport;
        float m_clear_depth;
        VideoDriver* m_video_driver;

    private:
        RenderTarget(const RenderTarget&) = delete;
        RenderTarget& operator = (const RenderTarget&) = delete;
    };

}

#endif	//	_H_PUNK_GPU_RENDER_TARGET
