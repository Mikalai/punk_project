#include "../../system/module.h"
#include "../../scene/module.h"
#include "../../virtual/module.h"
#include "../../gpu/module.h"
#include "../../utility/module.h"
#include "../../ai/module.h"
#include "render_static_mesh.h"
#include "render_skin_mesh.h"
#include "render_armature.h"
#include "render_river.h"
#include "process_armature.h"
#include "process_light.h"
#include "process_material.h"
#include "process_terrain_mesh.h"
#include "process_sun.h"
#include "process_navi_mesh.h"
#include "process_transform.h"
#include "render_v2.h"

namespace Render
{

    Render2::Render2()
        : m_armature_mixer(nullptr)
    {
        RegisterRenderProcessor(Virtual::StaticGeometry::Info.Type.GetId(), ProcessStaticMesh);
        RegisterRenderProcessor(Virtual::SkinGeometry::Info.Type.GetId(), ProcessSkinMesh);
        RegisterRenderProcessor(Virtual::Transform::Info.Type.GetId(), ProcessTransform);
        RegisterRenderProcessor(Virtual::ArmatureAnimationMixer::Info.Type.GetId(), ProcessArmature);
        RegisterRenderProcessor(Virtual::Light::Info.Type.GetId(), ProcessLight);
        RegisterRenderProcessor(Virtual::Material::Info.Type.GetId(), ProcessMaterial);
        RegisterRenderProcessor(Virtual::TerrainMesh::Info.Type.GetId(), ProcessTerrainMesh);
        RegisterRenderProcessor(Virtual::Sun::Info.Type.GetId(), ProcessSun);
        RegisterRenderProcessor(AI::NaviMesh::Info.Type.GetId(), ProcessNaviMesh);
        RegisterRenderProcessor(Virtual::River::Info.Type.GetId(), ProcessRiver);
    }

    Render2::~Render2()
    {}

    Gpu::Frame* Render2::GetCurrentFrame()
    {
        return m_frame;
    }

    void Render2::RenderScene(Scene::SceneGraph *value, const Math::mat4 &view, const Math::mat4 &projection, Gpu::Frame *frame)
    {
        m_all_lights.clear();
        m_all_lights.reserve(16);
        m_frame = frame;
        m_frame->PushViewState();
        m_frame->SetViewMatrix(view);
        m_frame->SetProjectionMatrix(projection);
        for (auto object : *value)
        {
            Scene::Node* node = Cast<Scene::Node*>(object);
            if (!node)
                continue;
            Process(node);
        }
        m_frame->PopViewState();
    }

    void Render2::Process(Scene::Node *node)
    {
        System::Object* o = node->GetOrLoadData();
        m_frame->SetWorldMatrix(node->GetGlobalMatrix());
        if (o)
        {
            void (*F)(Render2*, Scene::Node*, System::Object*) = m_render_processor.at(o->GetType()->GetId());
            if (F)
            {
                F(this, node, o);
            }
            else
            {
                ProcessChildren(node);
            }
        }
    }

    void Render2::ProcessChildren(Scene::Node *node)
    {
        for (auto object : *node)
        {
            Scene::Node* n = As<Scene::Node*>(object);
            if (!n)
                continue;
            Process(n);
        }
    }

    void Render2::SetCurrentArmatureAnimationMixer(Virtual::ArmatureAnimationMixer* value)
    {
        m_armature_mixer = value;
    }

    Virtual::ArmatureAnimationMixer* Render2::GetCurrentArmatureAnimationMixer()
    {
        return m_armature_mixer;
    }

    void Render2::PushLocalMatrix(const Math::mat4 value)
    {
        m_local_matrix.push(value);
    }

    void Render2::PopLocalMatrix()
    {
        m_local_matrix.pop();
    }

    const Math::mat4 Render2::GetLocalMatrix()
    {
        return m_local_matrix.top();
    }

    void Render2::RegisterRenderProcessor(unsigned type, void (*F)(Render2 *, Scene::Node *, System::Object *))
    {
        if (type >= m_render_processor.size())
            m_render_processor.resize(type+1);
        m_render_processor[type] = F;
    }

    void Render2::AddLight(const Gpu::LightParameters &light)
    {
        m_all_lights.push_back(light);
    }

    size_t Render2::GetLightsCount()
    {
        return m_all_lights.size();
    }

    const Gpu::LightParameters& Render2::GetLight(int index)
    {
        return m_all_lights[index];
    }
}
