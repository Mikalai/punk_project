#ifndef SIMPLE_SHADOWMAP_RENDER_H
#define SIMPLE_SHADOWMAP_RENDER_H

#include "abstract_shadowmap_render.h"
#include "../lighting/module.h"
#include "../../../math/frustum.h"

namespace Gpu
{
    class Texture2D;
    class VideoDriver;
    class FrameBuffer;

    class SimpleShadowMapRender : public AbstractShadowMapRender
    {
    public:
        SimpleShadowMapRender(VideoDriver* driver);
        virtual Texture* GetShadowMap() override;
        virtual void Run(Frame* frame) override;
        virtual void SetLight(const LightParameters& value) override;
        virtual void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up) override;
        virtual AbstractShadowMapDebugVisualizer* GetDebugVisualizer() override;
        virtual VideoDriver* GetVideoDriver() override;
        virtual ~SimpleShadowMapRender();
    private:
        VideoDriver* m_driver;
        Texture2D* m_shadow_map;
        FrameBuffer* m_fb;
        LightParameters m_light;
        Math::FrustumCore m_frustum;
        Math::vec3 m_cam_pos;
        Math::vec3 m_cam_dir;
        Math::vec3 m_cam_up;
        Frame* m_frame;
        Math::vec2 m_z_range;
        Math::mat4 m_shadow_view;
        Math::mat4 m_shadow_proj;
        Math::mat4 m_shadow_crop;
        float m_min_x;
        float m_max_x;
        float m_min_y;
        float m_max_y;
    };
}

#endif // SIMPLE_SHADOWMAP_RENDER_H
