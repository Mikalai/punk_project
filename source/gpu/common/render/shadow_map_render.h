#ifndef SHADOW_MAP_RENDER_H
#define SHADOW_MAP_RENDER_H

#include "../../../math/frustum.h"
#include "../../../math/mat4.h"
#include "../lighting/module.h"

namespace Gpu
{
    class Frame;
    class FrameBuffer;
    class Texture2DArray;
    class VideoDriver;

    class ShadowMapRender
    {
    public:
        static const int MaxSplits = 4;
        static constexpr float SplitWeight = 0.75f;

        ShadowMapRender(VideoDriver* driver);
        ~ShadowMapRender();
        void SetLight(const LightParameters& value);
        void SetViewpoint(const Math::mat4& proj, const Math::mat4& view);
        void Run(Frame* frame);


    private:
        void UpdateSplits(Math::Frustum frustum[MaxSplits], float n, float f);
        float ApplyCropMatrix(Math::Frustum& frustum);

    private:
        Texture2DArray* m_shadow_maps;
        Frame* m_frame;
        LightParameters m_light;
        FrameBuffer* m_fb;
        Math::Frustum m_frustum[MaxSplits];
        Math::mat4 m_projection;
        Math::mat4 m_view;
        Math::mat4 m_shadow_view;
        Math::mat4 m_shadow_proj;
        Math::mat4 m_shadow_crop;
        Math::mat4 m_shadow_mvp;
        int m_splits_count;
        VideoDriver* m_driver;
    };
}

#endif // SHADOW_MAP_RENDER_H
