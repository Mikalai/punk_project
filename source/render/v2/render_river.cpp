#include "render_river.h"
#include "render_v2.h"
#include "../../scene/module.h"
#include "../../utility/module.h"
#include "../../virtual/module.h"

namespace Render
{
    void ProcessRiver(Render2* render, Scene::Node* node, System::Object* o)
    {
        if (!o)
            return;
        Virtual::River* river = (Virtual::River*)o;
        auto frame = render->GetCurrentFrame();
        frame->PushAllState();
        if (river)
        {
            Virtual::StaticGeometry* geom = river->GetGeometry();
            if (!geom)
            {
                if (!river->Task())
                {
                    auto name = river->GetStaticMeshFilename();
                    node->Graph()->AsyncParser()->Add(river->Task(new Utility::AsyncParserTask(Utility::FindPath(name))));
                }
                else
                {
                    if (river->Task()->State() == Utility::AsyncParserTask::AsyncSuccess)
                    {
                        System::Object* o = river->Task()->Release();
                        geom = As<Virtual::StaticGeometry*>(o);
                        if (geom)
                            river->SetGeometry(geom);
                        else
                            delete o;
                        river->Task(nullptr);
                    }
                    else if (river->Task()->State() == Utility::AsyncParserTask::AsyncFailed)
                    {
                        throw System::PunkException(L"Failed to load resource: " + river->Task()->Path());
                    }
                }
            }
            else
            {
                if (geom->GetGpuCache().IsOnGpu())
                {
                    frame->PushBatchState();
                    frame->EnableBlending(true);
                    frame->SetDiffuseColor(0, 0, 1, 0.5);
                    frame->SetTextureMatrix(Math::mat4::CreateTranslate(river->GetStreamPosition()));
                    frame->Submit(geom->GetGpuCache().GetGpuBuffer());
                    frame->PopBatchState();
                }
                else
                {
                    if (!geom->GetCpuCache().IsOnCpu())
                        geom->GetCpuCache().Update();
                    else
                        geom->GetGpuCache().Update(frame->GetVideoDriver());
                }
            }
        }
        render->ProcessChildren(node);
        frame->PopAllState();
    }
}
