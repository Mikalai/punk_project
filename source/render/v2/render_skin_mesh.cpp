#include "../../system/module.h"
#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "../../gpu/module.h"
#include "../../utility/module.h"
#include "render_v2.h"
#include "render_skin_mesh.h"

namespace Render
{
    void ProcessSkinMesh(Render2 *render, Scene::Node* node, System::Object* o)
    {
        if (!o)
            return;

        Virtual::SkinGeometry* geom = (Virtual::SkinGeometry*)o;
        auto frame = render->GetCurrentFrame();
        frame->PushAllState();

        Virtual::ArmatureAnimationMixer* mixer = render->GetCurrentArmatureAnimationMixer();
        Virtual::Armature* armature = mixer->GetArmature();
        //        if (!geom)
        //        {
        //            geom = Cast<Virtual::SkinGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + node->GetStorageName()));
        //            geom->SetFilename(node->GetStorageName());
        //            node->SetGeometry(geom);
        //        }
        if (geom)
        {
            if (geom->GetGpuCache().IsOnGpu())
            {
                frame->EnableSkinning(true);
                for (size_t bone_index = 0; bone_index != armature->GetBonesCount(); ++bone_index)
                {
                    frame->SetBoneMatrix(bone_index, render->GetLocalMatrix().Inversed() * mixer->GetAnimatedGlobalMatrix(bone_index) * render->GetLocalMatrix());
                }
                frame->Submit(geom->GetGpuCache().GetGpuBuffer());
                frame->EnableSkinning(false);
                if (frame->IsEnabledBoundingBoxRendering())
                {
                    const auto& bbox = geom->GetBoundingBox();
                    frame->Submit(Gpu::AsRenderable(bbox, frame->GetVideoDriver()), true);
                    Math::mat4 t;
                    t.SetColumn(0, Math::vec4(bbox.GetR(), 0));
                    t.SetColumn(1, Math::vec4(bbox.GetS(), 0));
                    t.SetColumn(2, Math::vec4(bbox.GetT(), 0));
                    t.SetColumn(3, Math::vec4(bbox.GetCenter().X()
                                              , bbox.GetCenter().Y()
                                              , bbox.GetCenter().Z()
                                              ,1));

                    frame->PushAllState();
                    Math::vec3 p (0,0,0);
                    //frame->SetWorldMatrix(Math::mat4::CreateIdentity());
                    p = bbox.GetMinCorner();
                    frame->EnableDepthTest(false);
                    frame->EnableTexturing(false);
                    frame->SetDiffuseColor(0, 1, 0,1);
                    frame->SetPointSize(10);
                    frame->DrawPoint(p);
                    frame->SetDiffuseColor(1, 0, 0, 1);
                    frame->DrawLine(p, p + bbox.GetR());
                    frame->SetDiffuseColor(0, 1, 0, 1);
                    frame->DrawLine(p, p + bbox.GetS());
                    frame->SetDiffuseColor(0, 0, 1, 1);
                    frame->DrawLine(p, p + bbox.GetT());
                    frame->PopAllState();
                }
                if (frame->IsEnabledBoundingSphereRendering())
                {
                    frame->Submit(Gpu::AsRenderable(geom->GetBoundingSphere(), frame->GetVideoDriver()), true);
                }
            }
            else
            {
                if (!geom->GetCpuCache().IsOnCpu())
                    geom->GetCpuCache().Update();
                else
                    geom->GetGpuCache().Update(armature, frame->GetVideoDriver());
            }
        }
        render->ProcessChildren(node);
        frame->PopAllState();
    }
}
