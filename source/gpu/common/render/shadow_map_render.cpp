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
    ShadowMapRender::Debug::Debug(ShadowMapRender& m)
        : m_frustum(m.m_frustum)
        , m_shadow_view(m.m_shadow_view)
        , m_shadow_crop(m.m_shadow_crop)
        , m_shadow_mvp(m.m_shadow_mvp)
        , m_shadow_proj(m.m_shadow_proj)
        , m_projection(m.m_projection)
        , m_view(m.m_view)
    {}

    ShadowMapRender::ShadowMapRender(VideoDriver* driver)
        : m_debug(*this)
        , m_driver(driver)
        , m_shadow_maps(nullptr)
        , m_fb(nullptr)
        , m_splits_count(4)
    {
        auto size = m_driver->GetCaps().ShadowMapSize;
        m_shadow_maps = m_driver->CreateTexture2DArray(size, size, m_splits_count,
                                                                        ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32F,
                                                                        ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT,
                                                                        ImageModule::IMAGE_DATA_TYPE_FLOAT, 0, false);
        m_shadow_maps->SetCompareFunction(TextureCompareFunc::TextureLessEqual);
        m_shadow_maps->SetCompareMode(TextureCompareMode::TextureNone);
        m_shadow_maps->SetMinFilter(TextureFilter::Linear);
        m_shadow_maps->SetMagFilter(TextureFilter::Linear);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::S, TextureWrapMode::ClampToEdge);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::R, TextureWrapMode::ClampToEdge);

        m_fb = m_driver->CreateFrameBuffer();
        m_fb->SetRenderTarget(FrameBufferTarget::TargetNone);
        m_fb->SetViewport(0, 0, size, size);
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

    void FindZRange(const Math::FrustumCore& frustum, const Math::mat4& shadow_view, Frame* frame, Math::vec2& z_range)
    {
        // find the z-range of the current frustum as seen from the light
        // in order to increase precision
        Math::vec4 transf = shadow_view * Math::vec4(frustum.point[0], 1.0f);
        float min_z = transf.Z();
        float max_z = transf.Z();

        for (int j = 1; j < 8; ++j)
        {
            transf = shadow_view * Math::vec4(frustum.point[j], 1.0f);
            if (transf.Z() > max_z)
                max_z = transf.Z();
            if (transf.Z() < min_z)
                min_z = transf.Z();
        }

        for (Batch* o : frame->GetBatches())
        {
            transf = shadow_view*o->m_state->batch_state->m_bsphere.GetCenter();
            if (transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius() > max_z)
                max_z = transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius();
//            if (transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius() < min_z)
//                min_z = transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius();
        }
        z_range.Set(min_z, max_z);
    }

    const Math::mat4 FindLightProjectionMatrix(const Math::vec2& z_range)
    {
        // set the projection matrix with the new z-bounds
        // note the inversion because the light looks at the neg.
        auto projection = Math::mat4::CreateOrthographicProjection(-1.0, 1.0, -1.0, 1.0, -z_range[1], -z_range[0]);
        return projection;
    }

    const Math::mat4 FindCropMatrix(const Math::FrustumCore &frustum, const Math::mat4 &shadow_view, const Math::mat4& shadow_proj, float& min_x, float& max_x, float& min_y, float& max_y)
    {
        max_x = -std::numeric_limits<float>::infinity();
        min_x = std::numeric_limits<float>::infinity();
        max_y = -std::numeric_limits<float>::infinity();
        min_y = std::numeric_limits<float>::infinity();
        auto shadow_proj_view = shadow_proj * shadow_view;

        // find the extends of the frustum slice as projected in light's homogeneous coordinates
        for (int j = 0; j < 8; ++j)
        {
            auto transf = shadow_proj_view * Math::vec4(frustum.point[j], 1.0f);
            float x = transf.X() / transf.W();
            float y = transf.Y() / transf.W();

            if (x > max_x)
                max_x = x;
            if (x < min_x)
                min_x = x;
            if (y > max_y)
                max_y = y;
            if (y < min_y)
                min_y = y;
        }

        float scaleX = 2.0f / (max_x - min_x);
        float scaleY = 2.0f / (max_y - min_y);
        float offsetX = -0.5f * (max_x + min_x) * scaleX;
        float offsetY = -0.5f * (max_y + min_y) * scaleY;

        Math::mat4 crop_matrix;
        crop_matrix[0] = scaleX;
        crop_matrix[1 * 4 + 1] = scaleY;
        crop_matrix[3] = offsetX;
        crop_matrix[1 * 4 + 3] = offsetY;
        crop_matrix = crop_matrix.Transposed();
        return crop_matrix;
    }

    void ShadowMapRender::UpdateSplits(Math::FrustumCore frustum[MaxSplits], float n, float f)
    {
        float lambda = SplitWeight;
        float ratio = f/n;
        frustum[0].neard = n;

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
            frustum[i].neard = lambda*(n*powf(ratio, si)) + (1.0f-lambda)*(n + (f - n)*si);
            frustum[i-1].fard = frustum[i].neard * 1.005f;
            //frustum[i-1].Update();
            //m_projection[i-1] = m_frustum[i-1].GetProjectionMatrix();
        }
        frustum[m_splits_count-1].fard = f;
        //frustum[m_splits_count-1].Update();
    }

    const Math::mat4 GetBiasMatrix()
    {
        const float bias[16] = {	0.5f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.5f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.5f, 0.0f,
                                    0.5f, 0.5f, 0.5f, 1.0f	};
        Math::mat4 b;
        for (int i = 0; i != 16; ++i)
        {
            b[i] = bias[i];
        }

        return b;
    }

    const Math::mat4 CreateProjectionMatrix2(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
    {
        Math::mat4 m;
        m[0] = 2.0 / (xmax - xmin);
        m[1] = 0;
        m[2] = 0;
        m[3] = 0;

        m[4] = 0;
        m[5] = 2.0 / (ymax - ymin);
        m[6] = 0;
        m[7] = 0;

        m[8] = 0;
        m[9] = 0;
        m[10] = -2.0 / zmax;
        m[11] = 0;

        m[12] = - (xmax + xmin) / (xmax - xmin);
        m[13] = - (ymax + ymin) / (ymax - ymin);
        m[14] = -1;
        m[15] = 1;
        return m;
    }

    void ShadowMapRender::Run(Frame *frame)
    {
        m_frame = frame;
        auto batches = m_frame->GetBatches();
        for (int i = 0; i < m_splits_count; ++i)
        {
            m_shadow_view[i] = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,0), m_light.GetDirection().XYZ(), Math::vec3(-1, 0, 0));
        }

        UpdateSplits(m_frustum, m_near, m_far);

        m_fb->SetViewport(0, 0, m_driver->GetCaps().ShadowMapSize, m_driver->GetCaps().ShadowMapSize);
        for (auto i = 0; i != m_splits_count; ++i)
        {                       
            //m_frustum[i].Update();
            Math::FrustumTransform(m_frustum[i], m_cam_center, m_cam_dir, m_cam_up);

            FindZRange(m_frustum[i], m_shadow_view[i], m_frame, m_z_range[i]);
            m_shadow_proj[i] = FindLightProjectionMatrix(m_z_range[i]);
            m_shadow_crop[i] = FindCropMatrix(m_frustum[i], m_shadow_view[i], m_shadow_proj[i], m_min_x[i], m_max_x[i], m_min_y[i], m_max_y[i]);

            //m_shadow_proj[i] = CreateProjectionMatrix2(m_min_x[i], m_max_x[i], m_min_y[i], m_max_y[i], m_z_range[i][0], m_z_range[i][1]);

            m_fb->AttachDepthTarget(m_shadow_maps, i);
            m_fb->SetRenderTarget(Gpu::FrameBufferTarget::TargetNone);
            m_fb->Clear(false, true, false);
            m_fb->Bind();            
            m_fb->SetPolygonOffset(1.0f, 4096.0f);
            auto policy = AbstractRenderPolicy::find(RenderPolicySet::DepthRender);
            policy->Begin();
            for (Batch* batch : batches)
            {

                auto old_proj = batch->m_state->view_state->m_projection;
                auto old_view = batch->m_state->view_state->m_view;
                batch->m_state->view_state->m_projection = m_shadow_crop[i] * m_shadow_proj[i];
               // batch->m_state->view_state->m_projection = m_shadow_proj[i];
                batch->m_state->view_state->m_view = m_shadow_view[i];
                batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, m_shadow_crop[i] * m_shadow_proj[i] * m_shadow_view[i]);
                //batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, GetBiasMatrix() * m_shadow_proj[i] * m_shadow_view[i]);
                float far_bound = 0.5f*(-m_frustum[i].fard * old_proj[10] + old_proj[14])/m_frustum[i].fard + 0.5f;
                batch->m_state->light_state->m_lights[0].SetFarDistance(i, far_bound);
                batch->m_state->texture_state->m_texture_array = m_shadow_maps;
                batch->m_state->texture_state->m_texture_array_slot = 7;
                batch->m_state->texture_state->m_texture_array_shadow_map_layer[i] = i;
                batch->m_state->light_state->m_lights[0].SetPosition(m_light.GetPosition().XYZ());
                batch->m_state->light_state->m_lights[0].SetDirection(m_light.GetDirection().XYZ());
                batch->m_state->light_state->m_lights[0].SetFarZ(m_z_range[i][1]);
                batch->m_state->light_state->m_lights[0].SetNearZ(m_z_range[i][0]);


                policy->BindParameters(*batch->m_state);
                batch->m_renderable->Bind(policy->GetRequiredAttributesSet());
                batch->m_renderable->Render();
                batch->m_renderable->Unbind();                

                //batch->m_state->view_state->m_projection = m_shadow_crop[i] * m_shadow_proj[i];
                //batch->m_state->view_state->m_view = m_shadow_view[i];
                batch->m_state->view_state->m_projection = old_proj;
                batch->m_state->view_state->m_view = old_view;
            }
            m_fb->SetPolygonOffset(0, 0);
            policy->End();
            m_fb->Unbind();
        }
    }

    Texture2DArray* ShadowMapRender::GetShadowMaps()
    {
        return m_shadow_maps;
    }

    void ShadowMapRender::SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3 &center, const Math::vec3 &dir, const Math::vec3 &up)
    {
        m_cam_center = center;
        m_cam_dir = dir;
        m_cam_up = up;        
        m_near = n;
        m_far = f;

        for (int i = 0; i != MaxSplits; ++i)
        {
            m_frustum[i].ratio = aspect;
            m_frustum[i].fov = fov + 0.2f;
            m_view[i] = Math::mat4::CreateTargetCameraMatrix(center, center + dir, up);
            m_projection[i] = Math::mat4::CreatePerspectiveProjection(fov, aspect, 1, m_near, m_far);
        }        
    }

    int ShadowMapRender::GetSplitCount() const
    {
        return m_splits_count;
    }

    void ShadowMapRender::SetSplitCount(int value)
    {
        m_splits_count = value;
    }
}
