#include "simple_shadowmap_render.h"
#include "../video_driver.h"
#include "../video_driver_caps.h"
#include "../texture/texture2d.h"
#include "../frame_buffer/module.h"
#include "shadow_render_common.h"
#include "render_batch.h"
#include "../frame.h"
#include "../gpu_state.h"
#include "../abstract_render_context_policy.h"
#include "../renderable.h"

namespace Gpu
{
    SimpleShadowMapRender::SimpleShadowMapRender(VideoDriver *driver)
        : m_driver(driver)
    {
        auto size = m_driver->GetCaps().ShadowMapSize;
        m_shadow_map = m_driver->CreateTexture2D(size, size, ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32F,
                                                 ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT,
                                                 ImageModule::IMAGE_DATA_TYPE_FLOAT, 0, false);

        m_shadow_map->SetCompareFunction(TextureCompareFunc::TextureLessEqual);
        m_shadow_map->SetCompareMode(TextureCompareMode::TextureNone);
        m_shadow_map->SetMinFilter(TextureFilter::Linear);
        m_shadow_map->SetMagFilter(TextureFilter::Linear);
        m_shadow_map->SetWrapMode(TextureWrapDirection::S, TextureWrapMode::ClampToEdge);
        m_shadow_map->SetWrapMode(TextureWrapDirection::R, TextureWrapMode::ClampToEdge);

        m_fb = m_driver->CreateFrameBuffer();
        m_fb->SetRenderTarget(FrameBufferTarget::TargetNone);
        m_fb->SetViewport(0, 0, size, size);
    }

    SimpleShadowMapRender::~SimpleShadowMapRender()
    {
        safe_delete(m_shadow_map);
        safe_delete(m_fb);
    }

    Texture* SimpleShadowMapRender::GetShadowMap()
    {
        return m_shadow_map;
    }

    void SimpleShadowMapRender::Run(Frame* frame)
    {
        m_frame = frame;
        auto batches = m_frame->GetBatches();
        m_shadow_view = Math::mat4::CreateTargetCameraMatrix(m_light.GetPosition().XYZ(), m_light.GetPosition().XYZ() + m_light.GetDirection().XYZ(), {0, 0, 1});
        Math::FrustumTransform(m_frustum, m_cam_pos, m_cam_dir, m_cam_up);
        FindZRange(m_frustum, m_shadow_view, m_frame, m_z_range);
        m_shadow_proj = Math::mat4::CreateLightProjectionMatrix(m_z_range);
        m_shadow_crop = Math::mat4::CreateCropMatrix(m_frustum, m_shadow_view, m_shadow_proj, m_min_x, m_max_x, m_min_y, m_max_y);

        m_fb->AttachDepthTarget(m_shadow_map);
        m_fb->SetRenderTarget(Gpu::FrameBufferTarget::TargetNone);
        m_fb->Clear(false, true, false);
        m_fb->Bind();
        // m_fb->SetPolygonOffset(1.0f, 4096.0f);
        auto policy = AbstractRenderPolicy::find(RenderPolicySet::DepthRender);
        policy->Begin();
        for (Batch* batch : batches)
        {

            auto old_proj = batch->m_state->view_state->m_projection;
            auto old_view = batch->m_state->view_state->m_view;
            batch->m_state->view_state->m_projection = m_shadow_crop * m_shadow_proj;
           // batch->m_state->view_state->m_projection = m_shadow_proj[i];
            batch->m_state->view_state->m_view = m_shadow_view;
            batch->m_state->light_state->m_lights[0].SetShadowMatrix(0, m_shadow_crop * m_shadow_proj * m_shadow_view);
            //batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, GetBiasMatrix() * m_shadow_proj[i] * m_shadow_view[i]);
            batch->m_state->texture_state->m_shadow_map = m_shadow_map;
            batch->m_state->texture_state->m_shadow_map_slot = 7;
            batch->m_state->light_state->m_lights[0].SetPosition(m_light.GetPosition().XYZ());
            batch->m_state->light_state->m_lights[0].SetDirection(m_light.GetDirection().XYZ());
            batch->m_state->light_state->m_lights[0].SetFarZ(m_z_range[1]);
            batch->m_state->light_state->m_lights[0].SetNearZ(m_z_range[0]);

            policy->BindParameters(*batch->m_state);
            batch->m_renderable->Bind(policy->GetRequiredAttributesSet());
            batch->m_renderable->Render();
            batch->m_renderable->Unbind();

            batch->m_state->view_state->m_projection = old_proj;
            batch->m_state->view_state->m_view = old_view;
        }
        m_fb->SetPolygonOffset(0, 0);
        policy->End();
        m_fb->Unbind();
    }

    void SimpleShadowMapRender::SetLight(const LightParameters& value)
    {
        m_light = value;
    }

    void SimpleShadowMapRender::SetViewProperties(float fov, float aspect, float n, float f,
                                                  const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up)
    {
        m_frustum.fard = f;
        m_frustum.neard = n;
        m_frustum.fov = fov;
        m_frustum.ratio = aspect;
        m_cam_pos = center;
        m_cam_dir = dir;
        m_cam_up = up;
    }

    AbstractShadowMapDebugVisualizer* SimpleShadowMapRender::GetDebugVisualizer()
    {
        return nullptr;
    }

    VideoDriver* SimpleShadowMapRender::GetVideoDriver()
    {
        return m_driver;
    }
}
