#ifndef RENDER_TEXTURE_DEPTH_H
#define RENDER_TEXTURE_DEPTH_H

#include "../../common/render_target.h"

namespace Gpu
{
    class Texture2D;

    namespace OpenGL
    {
        class RenderTargetTextureDepth : public RenderTarget
        {
        public:
            RenderTargetTextureDepth(Texture2D* depth_buffer, VideoDriver* driver);
            virtual void SetViewport(const Math::Rect& value) override;
            virtual void Activate() override;
            virtual void Deactivate() override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual ~RenderTargetTextureDepth();

        private:
            void Check();

        private:
            Texture2D* m_depth_buffer;
            unsigned m_fb;
        };
    }
}

#endif // RENDER_TEXTURE_DEPTH_H
