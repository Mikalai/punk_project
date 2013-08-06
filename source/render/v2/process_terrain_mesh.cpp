#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "../../utility/module.h"
#include "render_v2.h"
#include "process_terrain_mesh.h"

namespace Render
{
    void ProcessTerrainMesh(Render2 *render, Scene::Node *node, System::Object* o)
    {
        Virtual::TerrainMesh *terrain = (Virtual::TerrainMesh*)o;
        auto m_frame = render->GetCurrentFrame();
        m_frame->PushAllState();
        if (terrain)
        {
            Virtual::StaticGeometry* geom = terrain->GetGeometry();            
            if (!geom)
            {
                if (!terrain->Task())
                {
                    auto name = terrain->GetStaticMeshFilename();
                    render->AsyncParser()->Add(terrain->Task(new Utility::AsyncParserTask(Utility::FindPath(name))));
                }
                else
                {
                    if (terrain->Task()->State() == Utility::AsyncParserTask::AsyncSuccess)
                    {
                        System::Object* o = terrain->Task()->Release();
                        geom = As<Virtual::StaticGeometry*>(o);
                        if (geom)
                            terrain->SetGeometry(geom);
                        else
                            delete o;
                        terrain->Task(nullptr);
                    }
                    else if (terrain->Task()->State() == Utility::AsyncParserTask::AsyncFailed)
                    {
                        throw System::PunkException(L"Failed to load resource: " + terrain->Task()->Path());
                    }
                }
            }
            else
            {
                if (geom->GetGpuCache().IsOnGpu())
                    m_frame->Render(geom->GetGpuCache().GetGpuBuffer());
                else
                {
                    if (!geom->GetCpuCache().IsOnCpu())
                        geom->GetCpuCache().Update();
                    else
                        geom->GetGpuCache().Update(m_frame->GetVideoDriver());
                }
            }
        }
        render->ProcessChildren(node);
        m_frame->PopAllState();
    }
}
