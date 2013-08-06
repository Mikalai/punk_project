#ifndef RENDER_TARGET_TEXTURE_COLOR_H
#define RENDER_TARGET_TEXTURE_COLOR_H

#include "../../common/render_target.h"

namespace Gpu
{
    class Texture2D;

    namespace OpenGL
    {
        class RenderTargetTextureColor : public RenderTarget
        {
        public:
            RenderTargetTextureColor(Texture2D* color_buffer, VideoDriver* driver);
            virtual void SetViewport(const Math::Rect& value) override;
            virtual void Activate() override;
            virtual void Deactivate() override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual ~RenderTargetTextureColor();
        private:
            void Check();

        private:
            Texture2D* m_color_buffer;
            unsigned m_fb;
            unsigned m_depth_rb;
        };
    }
}

#endif // RENDER_TARGET_TEXTURE_COLOR_H
