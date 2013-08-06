#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_light.h"

namespace Render
{
    void ProcessLight(Render2 *render, Scene::Node *node, System::Object *o)
    {
        if (!o)
            return;
        Virtual::Light* light = (Virtual::Light*)o;
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushLightState();
        if (light)
        {
            Virtual::PointLight* p = Cast<Virtual::PointLight*>(light);
            if (p)
            {
                m_frame->Light(0).SetDiffuseColor(p->GetColor());
                m_frame->Light(0).SetLightAttenuation(Gpu::LightAttenuation::Quadratic);
                m_frame->Light(0).SetLightConstantAttenuation(0);
                m_frame->Light(0).SetLightLinearAttenuation(p->GetLinearAttenuation());
                m_frame->Light(0).SetLightQuadricAttenuation(p->GetQuadraticAttenuation());
                m_frame->Light(0).SetType(Gpu::LightType::Point);
                m_frame->Light(0).SetPosition(m_frame->GetWorldMatrix().TranslationPart());
            }
        }
        render->ProcessChildren(node);
        m_frame->PopLightState();
    }
}
