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

        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
            auto n = m_node->Find(L"parent_transform", true);
            switch(event->key)
            {
            case System::PUNK_KEY_Q:
                n->Rotate(Math::quat::CreateFromAngleAxis(0.1, {1, 0, 0}));
                break;
            case System::PUNK_KEY_E:
                n->Rotate(Math::quat::CreateFromAngleAxis(-0.1, {1, 0, 0}));
                break;
            }
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
                static float angle = 0;
                angle += event->elapsed_time_s;
             //   n->Rotate(Math::quat::CreateFromAngleAxis(event->elapsed_time_s, {-1,0,0}));
         //       n->Translate({sin(angle)*0.5f, cos(angle)*0.5f, 0});
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
            Math::mat4 m = Math::mat4::CreateTargetCameraMatrix({0, -15, 0}, {0, 0, 0}, {0, 0, 1});
            m = GetViewMatrix();
            render.RenderScene(m_node, m, GetProjectionMatrix(), frame);
            frame->PopAllState();
            frame->BeginRendering();
            frame->SetClearColor(0.4, 0.4, 0.4, 1);
            frame->Clear(true, true, true);
            frame->PushAllState();
            {
                frame->SetWorldMatrix(Math::mat4::CreateIdentity());
                frame->SetViewMatrix(m);
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

