#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_armature.h"

namespace Render
{
    void ProcessArmature(Render2 *render, Scene::Node* node, System::Object* o)
    {
        Virtual::ArmatureAnimationMixer* mixer = (Virtual::ArmatureAnimationMixer*)o;
        auto frame = render->GetCurrentFrame();
        frame->PushAllState();
        render->SetCurrentArmatureAnimationMixer(mixer);
        render->ProcessChildren(node);
        frame->PopAllState();
    }
}
