#include "../frame.h"
#include "../video_driver.h"
#include "../texture/texture2d_array.h"
#include "cascade_shadow_map_debug_visualizer.h"
#include "cascade_shadow_map_render.h"

namespace Gpu
{
    CascadeShadowMapDebugVisualizer::CascadeShadowMapDebugVisualizer(CascadeShadowMapRender* value)
        : m_shadow_map_render(value)
    {
    }

    void CascadeShadowMapDebugVisualizer::Draw(Frame *frame)
    {
        //draw shadow maps
        frame->BeginRendering();
        frame->PushAllState();
        frame->EnableTexturing(true);
        frame->EnableLighting(false);
        frame->SetTexture2DArray(dynamic_cast<Gpu::Texture2DArray*>(m_shadow_map_render->GetShadowMap()), 0);
        frame->SetViewMatrix(Math::mat4::CreateIdentity());
        frame->SetProjectionMatrix(Math::mat4::CreateOrthographicProjection(0, m_shadow_map_render->GetVideoDriver()->GetWindow()->GetWidth(), 0, m_shadow_map_render->GetVideoDriver()->GetWindow()->GetHeight(), -1, 1));
        for (int i = 0; i < m_shadow_map_render->GetSplitCount(); ++i)
        {
            frame->SetDiffuseMapIndex(0, i);
            frame->EnableTexturing(true);
            frame->DrawQuad(10 + 260*i, 10, 256, 256);
        }
        frame->PopAllState();
        frame->EndRendering();

//        frame->BeginRendering();
//        frame->PushAllState();
//        frame->EnableTexturing(false);
//        frame->EnableLighting(false);
//        frame->SetTexture2DArray(nullptr, -1);
//        for (int i = 0; i < m_shadow_map_render->GetSplitCount(); ++i)
//        {
//            if (i == 0)
//                frame->SetDiffuseColor(1, 0, 0, 1);
//            else if (i == 1)
//                frame->SetDiffuseColor(0, 1, 0, 1);
//            else if (i == 2)
//                frame->SetDiffuseColor(0, 0, 1, 1);
//            else if (i == 3)
//                frame->SetDiffuseColor(1, 1, 0, 1);

//            {
//                Math::FrustumCore f(Math::FrustumCreateFromProjectionMatrix(m_projection_matrix));
//                Math::FrustumTransform(f, m_cam_pos, m_cam_dir, m_cam_up);
//                frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//                frame->SetDiffuseColor(0, 1, 0, 1);
//                frame->Render(Gpu::AsRenderable2(f, GetVideoDriver()), true);
//            }

//            if (!alternative_view)
//            {
//                frame->SetViewMatrix(m_view_matrix);
//                frame->SetProjectionMatrix(m_projection_matrix);
//            }
//            else
//            {
//                frame->SetViewMatrix(m_view_matrix_a);
//                frame->SetProjectionMatrix(m_proj_matrix_a);
//            }

//            frame->SetDiffuseColor(1, 0, 0, 1);
//            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//            frame->Render(Gpu::AsRenderable2(m_shadow_map_render->m_debug.m_frustum[i], GetVideoDriver()), true);

//            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//            frame->SetPointSize(10);
//            Gpu::RenderableBuilder b(GetVideoDriver());
//            b.Begin(Gpu::PrimitiveType::POINTS);
//            for (int j = 0; j != 8; ++j)
//            {
//                b.Vertex3fv(m_shadow_map_render->m_debug.m_frustum[i].point[j]);
//            }
//            b.End();
//            frame->Render(b.ToRenderable(), true);

//            if (!alternative_view)
//            {
//                frame->SetViewMatrix(m_view_matrix);
//                frame->SetProjectionMatrix(m_projection_matrix);
//            }
//            else
//            {
//                frame->SetViewMatrix(m_view_matrix_a);
//                frame->SetProjectionMatrix(m_proj_matrix_a);
//            }
//            // frame->SetProjectionMatrix(m_projection_matrix);
//            frame->SetWorldMatrix(m_shadow_map_render->m_debug.m_shadow_view[i].Inversed());
//            Math::FrustumCore f(Math::FrustumCreateFromProjectionMatrix(m_shadow_map_render->m_debug.m_shadow_crop[i] * m_shadow_map_render->m_debug.m_shadow_proj[i]));
//            frame->Render(Gpu::AsRenderable(f, GetVideoDriver()), true);
//        }
//        frame->PopAllState();
    }
}
