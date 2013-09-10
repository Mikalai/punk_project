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

    Render2::Render2(Utility::AsyncParser* parser)
        : m_camera(nullptr)
        , m_armature_mixer(nullptr)
        , m_parser(parser)
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

    void Render2::RenderScene(Scene::SceneGraph* value, Gpu::Frame* frame)
    {
        m_all_lights.clear();
        m_all_lights.reserve(16);
        m_frame = frame;
        m_frame->PushViewState();
        if (m_camera)
        {
            m_frame->SetViewMatrix(m_camera->GetViewMatrix());
            m_frame->SetProjectionMatrix(m_camera->GetProjectionMatrix());
        }
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
        System::Object* o = node->GetData();
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
        else
        {
            LoadObject(node);
            ProcessChildren(node);
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

    void Render2::SetCamera(Virtual::Camera *value)
    {
        m_camera = value;
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

    Utility::AsyncParser* Render2::AsyncParser()
    {
        return m_parser;
    }

    void Render2::AsyncParser(Utility::AsyncParser* parser)
    {
        m_parser = parser;
    }

    void Render2::LoadObject(Scene::Node *node)
    {
        if (!node->Task())
        {
            //  if node has got no data and there was no task to load data, than try to load data into the node
            auto name = node->GetName();
            AsyncParser()->Add(node->Task(new Utility::AsyncParserTask(Utility::FindPath(name))));
        }
        else
        {
            //  node has got no data and we assigned loading task to the node
            if (node->Task()->State() == Utility::AsyncParserTask::AsyncSuccess)
            {
                //  if loading complete succesfull, move object from task to node data
                node->SetData(node->Task()->Release());
                //  delete node task (now we have and object). If something will delete object from
                //  the node, we will create it again, because the will not be any tasks assigned to
                //  the node
                node->Task(nullptr);
            }
            else if (node->Task()->State() == Utility::AsyncParserTask::AsyncFailed)
            {
                //  if loading failed to complete there is no reason to continue work.
                //  TODO: Maybe it is possible to continue work, when failed to load
                throw System::PunkException(L"Failed to load resource: " + node->Task()->Path());
            }
        }
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
