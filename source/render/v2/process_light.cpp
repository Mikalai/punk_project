#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_light.h"

namespace Render
{
    void ProcessPointLight(Render2 *render, Scene::Node *node, System::Object *o)
    {
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushLightState();
        render->ProcessChildren(node);
        m_frame->PopLightState();
    }

    void ProcessDirectionalLight(Render2 *render, Scene::Node *node, System::Object *o)
    {
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushLightState();
        render->GetCurrentFrame()->DrawPoint(node->GlobalPosition());
        Virtual::DirectionalLight* l = Cast<Virtual::DirectionalLight*>(o);
        m_frame->Submit(Gpu::AsRenderable(node->GlobalPosition(), node->GlobalPosition() + 3 * node->GlobalRotation().Rotate(l->GetDirection()),
                          render->GetCurrentFrame()->GetVideoDriver()), true);
        render->ProcessChildren(node);
        m_frame->PopLightState();
    }

    void ProcessSpotLight(Render2 *render, Scene::Node *node, System::Object *o)
    {
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushLightState();
        render->ProcessChildren(node);
        m_frame->PopLightState();
    }

    void ProcessLight(Render2 *render, Scene::Node *node, System::Object *o)
    {
        if (!o)
            return;
        if (o->GetType()->IsEqual(&Virtual::PointLight::Info.Type))
            ProcessPointLight(render, node, o);
        else if (o->GetType()->IsEqual(&Virtual::DirectionalLight::Info.Type))
            ProcessDirectionalLight(render, node, o);
        else if (o->GetType()->IsEqual(&Virtual::SpotLight::Info.Type))
            ProcessSpotLight(render, node, o);
        auto frame = render->GetCurrentFrame();
        frame->PushAllState();
        frame->SetWorldMatrix(Math::mat4());
        frame->SetPointSize(10);
        frame->SetDiffuseColor(1, 1, 0, 1);
        frame->PopAllState();
    }
}
