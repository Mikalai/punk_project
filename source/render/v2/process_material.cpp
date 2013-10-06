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
            bool enable_textures = false;
            bool enable_bump = false;
            for (size_t i = 0; i != material->GetTextureSlotCount(); ++i)
            {
                if (!material->GetTextureSlot(i)->GetGpuCache().IsOnGpu())
                {
                    material->GetTextureSlot(i)->GetGpuCache().Update(m_frame->GetVideoDriver());                    
                }
                else
                {
                    if (material->GetTextureSlot(i)->IsDiffuseMapSlot())
                    {
                        m_frame->SetDiffuseMap(0, material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 0);
                        enable_textures = true;
                    }
                    if (material->GetTextureSlot(i)->IsNormalMapSlot())
                    {
                        m_frame->SetNormalMap(material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 1);
                        enable_bump = true;

                    }
                    if (material->GetTextureSlot(i)->IsSpecularIntensityMapSlot())
                    {
                        m_frame->SetSpecularMap(material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 2);
                        enable_textures = true;
                    }
                }
            }
            if (enable_textures)    //  TODO: check force texturing flag
            {
                m_frame->EnableTexturing(enable_textures);
            }
            else
            {
                m_frame->EnableTexturing(enable_textures);
            }

            if (enable_bump)        //  TODO: check force bump enable flag
            {
                m_frame->SetLightModel(Gpu::LightModel::BumpMappingDiffuse);
            }
            else
            {
                m_frame->SetLightModel(Gpu::LightModel::PerFragmentDiffuse);
            }
        }
        render->ProcessChildren(node);
        m_frame->PopAllState();
    }
}
