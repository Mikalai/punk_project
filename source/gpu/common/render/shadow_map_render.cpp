#include "../texture/module.h"
#include "../renderable.h"
#include "../../../math/perspective_decoder.h"
#include "../frame_buffer/module.h"
#include "shadow_map_render.h"
#include "render_batch.h"
#include "../frame.h"
#include "../video_driver.h"
#include "../video_driver_caps.h"
#include "render_pass.h"
#include "../abstract_render_context_policy.h"
#include "../video_driver.h"
#include "../gpu_state.h"

namespace Gpu
{
    ShadowMapRender::ShadowMapRender(VideoDriver* driver)
        : m_driver(driver)
        , m_shadow_maps(nullptr)
        , m_fb(nullptr)
        , m_splits_count(4)
    {
        auto size = m_driver->GetCaps().ShadowMapSize;
        m_shadow_maps = m_driver->CreateTexture2DArray(size, size, 4,
                                                                        ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT24,
                                                                        ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT,
                                                                        ImageModule::IMAGE_DATA_TYPE_FLOAT, 0, false);
        m_shadow_maps->SetCompareFunction(TextureCompareFunc::TextureLessEqual);
        m_shadow_maps->SetMinFilter(TextureFilter::Linear);
        m_shadow_maps->SetMagFilter(TextureFilter::Linear);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::S, TextureWrapMode::ClampToEdge);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::R, TextureWrapMode::ClampToEdge);

        m_fb = m_driver->CreateFrameBuffer();
        m_fb->SetRenderTarget(FrameBufferTarget::TargetNone);
        m_fb->SetViewport(0, 0, size, size);
    }

    void ShadowMapRender::SetViewpoint(const Math::mat4 &proj, const Math::mat4 &view)
    {
        m_projection = proj;
        m_view = view;
        Math::PerspectiveDecoder d(m_projection);
        for (int i = 0; i != MaxSplits; ++i)
        {
            m_frustum[i].SetAspectRatio(d.GetWidthToHeightAspectRatio());
            m_frustum[i].SetFovY(d.GetFovY() + 0.2f);
        }
    }

    ShadowMapRender::~ShadowMapRender()
    {
        safe_delete(m_shadow_maps);
        safe_delete(m_fb);
    }

    void ShadowMapRender::SetLight(const LightParameters &value)
    {
        m_light = value;
    }

    float ShadowMapRender::ApplyCropMatrix(Math::Frustum& frustum)
    {
        // find the z-range of the current frustum as seen from the light
        // in order to increase precision
        Math::vec4 transf = m_shadow_view * frustum.GetPoint((Math::Frustum::FrustumPoints)0);
        float min_z = transf.Z();
        float max_z = transf.Z();
        float max_x = -std::numeric_limits<float>::infinity();
        float min_x = std::numeric_limits<float>::infinity();
        float max_y = -std::numeric_limits<float>::infinity();
        float min_y = std::numeric_limits<float>::infinity();

        for (int i = 1; i < 8; ++i)
        {
            transf = m_shadow_view * frustum.GetPoint((Math::Frustum::FrustumPoints)i);
            if (transf.Z() > max_z)
                max_z = transf.Z();
            if (transf.Z() < min_z)
                min_z = transf.Z();
        }

        // make sure all relevant shadow casters are included
        // note that these here are dummy objects at the edges of our scene
        for (Batch* b : m_frame->GetBatches())
        {
            Math::BoundingSphere s = m_shadow_view * b->m_state->batch_state->m_bsphere;
            if (s.GetCenter().Z() + s.GetRadius() > max_z)
                max_z = s.GetCenter().Z() + s.GetRadius();
        }

        // set the projection matrix with the new z-bounds
        // note the inversion because the light looks at the neg.
        m_shadow_proj = Math::mat4::CreateOrthographicProjection(-1.0, 1.0, -1.0, 1.0, -max_z, -min_z);
        m_shadow_mvp = m_shadow_proj * m_shadow_view;

        // find the extends of the frustum slice as projected in light's homogeneous coordinates
        for (int i = 0; i < 8; ++i)
        {
            transf = m_shadow_mvp * frustum.GetPoint((Math::Frustum::FrustumPoints)i);
            transf.X() = transf.X() / transf.W();
            transf.Y() = transf.Y() / transf.W();

            if (transf.X() > max_x)
                max_x = transf.X();
            if (transf.X() < min_x)
                min_x = transf.X();
            if (transf.Y() > max_y)
                max_y = transf.Y();
            if (transf.Y() < min_y)
                min_y = transf.Y();
        }

        float scaleX = 2.0f/(max_x - min_x);
        float scaleY = 2.0f/(max_y - min_y);
        float offsetX = -0.5f*(max_x + min_x)*scaleX;
        float offsetY = -0.5f*(max_y + min_y)*scaleY;

        m_shadow_crop[0] = scaleX;
        m_shadow_crop[1 * 4 + 1] = scaleY;
        m_shadow_crop[3] = offsetX;
        m_shadow_crop[1 * 4 + 3] = offsetY;

        m_projection = m_shadow_crop * m_projection;

        return min_z;
    }

    void ShadowMapRender::UpdateSplits(Math::Frustum frustum[MaxSplits], float n, float f)
    {
        float lambda = SplitWeight;
        float ratio = f/n;
        frustum[0].SetNearPlane(n);
        frustum[0].Update();

        for(int i=1; i != m_splits_count; i++)
        {
            float si = i / (float)m_splits_count;

            //  as i understood, this allows us to combine two methods of calculating
            //  near and far distance.
            //  1. nd + (fd - nd)*si. Based on linear division of the frustum space. But
            //  as i remember perpsective projection is not linear, thus
            //  fd/nd influences on accuracy alot, and as bigger this value more artifacts
            //  we will have due to limits of the depth buffer. That's why there is a second
            //  aproach based on non linear distances. As i understood the goal is to make
            //  less distance between fd and nd for near splits and bigger distance for
            //  far splits. This will make near shadow nicier than far, but who cares abour far
            //  shadow :)
            frustum[i].SetNearPlane(lambda*(n*powf(ratio, si)) + (1-lambda)*(n + (f - n)*si));
            frustum[i].Update();
            frustum[i-1].SetFarPlane(frustum[i].GetNearPlane() * 1.005f);
        }
        frustum[m_splits_count-1].SetFarPlane(f);
        frustum[m_splits_count-1].Update();
    }

    void ShadowMapRender::Run(Frame *frame)
    {
        m_frame = frame;
        auto batches = m_frame->GetBatches();
        m_shadow_view = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,0), m_light.GetDirection().XYZ(), Math::vec3(0, 0, 1));


        UpdateSplits(m_frustum, 1.0f, 200.0f);

        for (auto i = 0; i != m_splits_count; ++i)
        {
            m_fb->AttachDepthTarget(m_shadow_maps, i);
            m_fb->Bind();
            m_fb->Clear(false, true, false);
            float min_z = ApplyCropMatrix(m_frustum[i]);

            for (Batch* batch : batches)
            {
                auto policy = AbstractRenderPolicy::find(RenderPolicySet::Solid3D);
                auto old_proj = batch->m_state->view_state->m_projection;
                auto old_view = batch->m_state->view_state->m_view;
                batch->m_state->view_state->m_projection = m_shadow_proj;
                batch->m_state->view_state->m_view = m_shadow_view;

                policy->Begin();
                policy->BindParameters(*batch->m_state);
                batch->m_renderable->Bind(policy->GetRequiredAttributesSet());
                batch->m_renderable->Render();
                batch->m_renderable->Unbind();
                policy->End();

                batch->m_state->view_state->m_projection = old_proj;
                batch->m_state->view_state->m_view = old_view;
            }
            m_fb->Unbind();
        }
    }
}
