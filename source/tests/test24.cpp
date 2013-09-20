#include "test24.h"

namespace Test24
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
            m_node = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder()
                                                                        + L"simple_scene.pmd"));
            std::cout << m_node->ToString() << std::endl;
        }

        virtual void OnDestroy() override
        {
            delete m_node;
        }

        virtual void OnRender(Gpu::Frame* frame) override
        {
            Scene::UpdateUpToDown(m_node);
            Math::vec3 point_light{2, 2, 2};
            Render::Render2 render;
            frame->EnableDiffuseShading(true);
            frame->EnableLighting(true);
            frame->SetLightModel(Gpu::LightModel::PerFragmentDiffuse);
            frame->EnableSpecularShading(true);
            frame->Light(0).Enable();
            frame->Light(0).SetType(Gpu::LightType::Point);
            frame->Light(0).SetPosition(point_light);
            render.RenderScene(m_node, GetViewMatrix(), GetProjectionMatrix(), frame);
            frame->BeginRendering();            
            frame->SetClearColor(0.4, 0.4, 0.4, 1);
            frame->Clear(true, true, true);

            frame->SetWorldMatrix(Math::mat4());
            frame->SetViewMatrix(GetViewMatrix());
            frame->SetProjectionMatrix(GetProjectionMatrix());
            frame->SetPointSize(10);
            frame->SetDiffuseColor(1,0,0,1);
            frame->DrawPoint(point_light);
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

