#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_transform.h"

namespace Render
{
    void ProcessTransform(Render2 *render, Scene::Node *node, System::Object *o)
    {
        if (!o)
            return;
        Virtual::Transform* value = (Virtual::Transform*)o;
        auto frame = render->GetCurrentFrame();
        frame->PushAllState();
        render->PushLocalMatrix(value->Get());
        frame->MultWorldMatrix(value->Get());
        render->ProcessChildren(node);
        render->PopLocalMatrix();
        frame->PopAllState();
    }
}
