#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_sun.h"

namespace Render
{
    void ProcessSun(Render2 *render, Scene::Node *node, System::Object* o)
    {
        if (!o)
            return;

        Virtual::Sun* sun = (Virtual::Sun*)o;
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushLightState();
//        Virtual::Sun* sun = node->GetSun();
//        if (!sun)
//        {
//            sun = Cast<Virtual::Sun*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + node->GetStorageName()));
//            if (sun)
//                node->SetSun(sun);
//        }
//        else
        {
            Math::vec3 pos(0,0,0);
            Math::vec4 dir(0, 0, -1, 0);
            dir = (m_frame->GetWorldMatrix() * dir).Normalized();
            pos = m_frame->GetWorldMatrix() * pos;
            m_frame->Light(0).Enable();
            m_frame->Light(0).SetDiffuseColor(sun->GetColor());
            m_frame->Light(0).SetType(Gpu::LightType::Direction);
           // m_frame->Light(0).SetPosition(m_frame->GetWorldMatrix().TranslationPart());
            m_frame->Light(0).SetPosition(pos);
            m_frame->Light(0).SetDirection(Math::vec3(dir.XYZ()).Normalized());
            m_frame->SetLightModel(Gpu::LightModel::PerFragmentDiffuse);
            render->AddLight(m_frame->Light(0));

            m_frame->PushAllState();
            m_frame->EnableTexturing(false);
            m_frame->EnableLighting(false);
            {
                Math::vec3 pos(0,0,0);
                Math::vec4 dir(0, 0, -1, 0);
                m_frame->Submit(Gpu::AsRenderable(pos, pos + dir.XYZ(), m_frame->GetVideoDriver()), true);
            }
            m_frame->PopAllState();
        }
        render->ProcessChildren(node);
        m_frame->PopLightState();
    }
}
