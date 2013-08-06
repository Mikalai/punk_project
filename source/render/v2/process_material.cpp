#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "render_v2.h"
#include "process_material.h"

namespace Render
{
    void ProcessMaterial(Render2 *render, Scene::Node *node, System::Object* o)
    {
        if (!o)
            return;
        Virtual::Material* material = (Virtual::Material*)o;

        auto m_frame = render->GetCurrentFrame();
        m_frame->PushAllState();
//        if (!material)
//        {
//            if (!node->GetStorageName().empty())
//            {
//                material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + node->GetStorageName()));
//                node->SetMaterial(material);
//            }
//        }
        if (material)
        {
            m_frame->SetAmbientColor(material->GetAmbient());
            m_frame->SetDiffuseColor(material->GetDiffuseColor());
            for (size_t i = 0; i != material->GetTextureSlotCount(); ++i)
            {
                if (!material->GetTextureSlot(i)->GetGpuCache().IsOnGpu())
                    material->GetTextureSlot(i)->GetGpuCache().Update(m_frame->GetVideoDriver());
                else
                {
                    if (material->GetTextureSlot(i)->IsDiffuseMapSlot())
                        m_frame->SetDiffuseMap0(material->GetTextureSlot(i)->GetGpuCache().GetTexture());
                    if (material->GetTextureSlot(i)->IsNormalMapSlot())
                    {
                        m_frame->SetNormalMap(material->GetTextureSlot(i)->GetGpuCache().GetTexture());
                        m_frame->SetLightModel(Gpu::LightModel::BumpMapping);
                    }
                    if (material->GetTextureSlot(i)->IsSpecularIntensityMapSlot())
                        m_frame->SetSpecularMap(material->GetTextureSlot(i)->GetGpuCache().GetTexture());
                }
            }
        }
        render->ProcessChildren(node);
        m_frame->PopAllState();
    }
}
