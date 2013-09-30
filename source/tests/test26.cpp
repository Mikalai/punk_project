#include "test26.h"

namespace Test26
{
    class TestApp : public Punk::ViewerApplication
    {
        Scene::SceneGraph* m_node;

    public:
        TestApp()
        {

        }

        virtual void OnInit(const Punk::Config&) override
        {
            SetCameraSpeed(5);
            m_node = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder()
                                                                        + L"simple_scene.pmd"));
            std::cout << m_node->ToString() << std::endl;
        }

        virtual void OnDestroy() override
        {
            delete m_node;
        }

        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event)
        {
            std::cout << m_node->ToString() << std::endl;
        }

        virtual void OnIdle(System::IdleEvent *event) override
        {
            Scene::Node* n = m_node->Find(L"Lamp_transform", true);
            if (n)
            {
                n->Rotate(Math::quat::CreateFromAngleAxis(event->elapsed_time_s, {1,0,0}));
            }

            n = m_node->Find(L"parent_transform", true);
            if (n)
            {
           //     n->Rotate(Math::quat::CreateFromAngleAxis(event->elapsed_time_s, {1,0,0}));
            }
        }

        virtual void OnRender(Gpu::Frame* frame) override
        {
            //Scene::UpdateUpToDown(m_node);
            m_node->Update();
            Math::vec3 point_light{2, 2, 2};
            Render::Render2 render;                        
            frame->EnableDiffuseShading(true);
            frame->EnableLighting(true);
            frame->EnableSpecularShading(true);
            frame->SetLightModel(Gpu::LightModel::PerFragmentDiffuse);

            frame->PushAllState();
            render.RenderScene(m_node, GetViewMatrix(), GetProjectionMatrix(), frame);
            frame->PopAllState();
            frame->BeginRendering();
            frame->SetClearColor(0.4, 0.4, 0.4, 1);
            frame->Clear(true, true, true);
            frame->PushAllState();
            {
                frame->SetWorldMatrix(Math::mat4::CreateIdentity());
                frame->SetViewMatrix(GetViewMatrix());
                frame->SetProjectionMatrix(GetProjectionMatrix());
                frame->DrawAxis();
            }
            frame->PopAllState();
            frame->EndRendering();
        }
    };

    void Test::Run()
    {
        m_result = true;
        try
        {
            TestApp* app = new TestApp;
            Punk::Config cfg;
            cfg.gpu_config.view_width = 800;
            cfg.gpu_config.view_height = 600;
            app->Init(cfg);
            System::Mouse::Instance()->LockInWindow(false);
            app->Run();
            delete app;
        }
        catch(System::PunkException& e)
        {
            out_error() << e.ToString() << std::endl;
            m_result = false;
        }
        catch(...)
        {
            m_result = false;
        }
    }

    bool Test::Succeed()
    {
        return m_result;
    }
}

