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
        void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up);
        void Run(Frame* frame);
        Texture2DArray* GetShadowMaps();
        int GetSplitCount() const;
        void SetSplitCount(int value);

        struct Debug
        {
            Debug(ShadowMapRender& m);

            Math::FrustumCore (&m_frustum)[MaxSplits];
            Math::mat4 (&m_shadow_view)[MaxSplits];
            Math::mat4 (&m_shadow_proj)[MaxSplits];
            Math::mat4 (&m_shadow_crop)[MaxSplits];
            Math::mat4 (&m_shadow_mvp)[MaxSplits];
            Math::mat4 (&m_projection)[MaxSplits];
            Math::mat4 (&m_view)[MaxSplits];
        };

        Debug m_debug;

    private:
        void UpdateSplits(Math::FrustumCore frustum[MaxSplits], float n, float f);

    private:
        Texture2DArray* m_shadow_maps;
        Frame* m_frame;
        LightParameters m_light;
        FrameBuffer* m_fb;
        Math::FrustumCore m_frustum[MaxSplits];
        Math::mat4 m_projection[MaxSplits];
        Math::mat4 m_view[MaxSplits];
        Math::vec3 m_cam_center;
        Math::vec3 m_cam_dir;
        Math::vec3 m_cam_up;
        Math::mat4 m_shadow_view[MaxSplits];
        Math::mat4 m_shadow_proj[MaxSplits];
        Math::mat4 m_shadow_crop[MaxSplits];
        Math::mat4 m_shadow_mvp[MaxSplits];
        Math::vec2 m_z_range[MaxSplits];
        float m_min_x[MaxSplits];
        float m_max_x[MaxSplits];
        float m_min_y[MaxSplits];
        float m_max_y[MaxSplits];
        int m_splits_count;
        VideoDriver* m_driver;        
        float m_near;
        float m_far;

        friend struct Debug;
    };
}

#endif // SHADOW_MAP_RENDER_H
