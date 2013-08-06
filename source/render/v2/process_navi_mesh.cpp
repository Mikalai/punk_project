#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_navi_mesh.h"

namespace Render
{
    void ProcessNaviMesh(Render2 *render, Scene::Node *node, System::Object* o)
    {
        if (!o)
            return;
        AI::NaviMesh *mesh = (AI::NaviMesh*)o;
        auto m_frame = render->GetCurrentFrame();
        if (m_frame->IsEnabledNaviMeshRendering())
        {
            if (mesh)
            {
                auto r = Gpu::AsRenderable(*mesh, m_frame->GetVideoDriver());
                m_frame->PushAllState();
                m_frame->EnableTexturing(false);
                m_frame->EnableLighting(false);
                m_frame->EnableBlending(true);
                m_frame->SetDiffuseColor(0, 0, 1.0, .5);
                m_frame->Render(r, true);
                m_frame->PopAllState();
            }
        }
        render->ProcessChildren(node);
    }
}
