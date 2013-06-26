#include "test19.h"

namespace Test19
{
    class TestApp : public Punk::Application
    {
        Scene::SceneGraph* m_scene;
        Virtual::Camera m_camera;
        Math::vec3 m_view_point;
        Math::vec3 m_camera_move;
        float m_camera_height;
        Math::mat4 m_projection_matrix;
        Math::mat4 m_view_matrix;
        std::vector<Scene::Selection> m_selection;
        Math::vec3 m_world_screen_point;
    public:
        TestApp()
        {
        }

        virtual void OnInit(const Punk::Config&) override
        {
            m_camera.SetPosition(3, 3, 3);
            m_camera.SetYawRollPitch(0, 0, -0.3);
            m_camera_height = 0.2;

            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            m_projection_matrix = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0);
            m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(.2, .2, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));

            m_scene = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"level_1.pmd"));
            if (!m_scene)
                return;
        }

        virtual void OnDestroy() override
        {
        }

        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event) override
        {
            Math::vec2 p(event->x, event->y);
            Math::vec2 s(GetWindow()->GetWidth(), GetWindow()->GetHeight());
            Scene::Selector selector(m_projection_matrix, m_view_matrix, p, s, 100.0f);
            selector.Select(m_scene);
            m_selection = selector.m_selections;
            m_world_screen_point = selector.m_world_screen_point;
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event)
        {
            m_camera_height += 0.1 * event->delta;            
        }

        virtual void OnMouseMove(System::MouseMoveEvent *event)
        {
       //     m_view_point[0] += 0.001 * float(event->x - event->x_prev);
        //    m_view_point[1] += 0.001 * float(event->y - event->y_prev);

            float m_camera_speed = 1;
            m_camera_move.Set(0,0,0);
            if (event->x < GetWindow()->GetWidth() / 10)
                m_camera_move[0] = m_camera_speed;
            if (event->x > GetWindow()->GetWidth() / 10 * 9)
                m_camera_move[0] = -m_camera_speed;
            if (event->y < GetWindow()->GetHeight() / 10)
                m_camera_move[1] = -m_camera_speed;
            if (event->y > GetWindow()->GetHeight() / 10 * 9)
                m_camera_move[1] = m_camera_speed;            
            UpdateViewMatrix();
        }

        void UpdateViewMatrix()
        {
            m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 0.2, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));
        }

        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
        }

        virtual void OnIdle(System::IdleEvent *event)
        {
            Virtual::River* river = Virtual::River::find(L"river_mesh");
            if (river)
            {
                river->SetStreamPosition(river->GetStreamPosition() + river->GetFlowSpeed() * river->GetFlowDirection() * event->elapsed_time_s);
            }
            if (m_camera_move != Math::vec3())
            {
                m_view_point += m_camera_move * event->elapsed_time_s;
                UpdateViewMatrix();
            }
            //m_camera.SetPosition(m_camera.GetPosition() + m_camera_move);
        }

        virtual void OnRender(GPU::Frame* frame) override
        {
            frame->PushAllState();

            frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
            frame->EnableDiffuseShading(true);
            frame->EnableTexturing(true);
            frame->EnableLighting(true);
            frame->SetViewMatrix(m_view_matrix);
            frame->SetProjectionMatrix(m_projection_matrix);
            frame->BeginRendering();
            frame->Clear(true, true, true);
            ::Render::Render2 render;
           // render.SetCamera(&m_camera);
            render.RenderScene(m_scene, frame);
            frame->DrawLine(0, 0, 1920, 1200);

            frame->PushAllState();
            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
            frame->EnableDepthTest(false);
            frame->SetPointSize(10);
            frame->DrawPoint(m_world_screen_point);
            for (Scene::Selection& s : m_selection)
            {                               
                for (auto p : s.GetPoints())
                {
                    frame->DrawPoint(p);
                }
            }
            frame->PopAllState();

            frame->EndRendering();

            frame->PopAllState();
        }
    };

    void Test::Run()
    {
        try
        {
            TestApp* app = new TestApp;
            Punk::Config cfg;
            cfg.gpu_config.view_width = 1920;
            cfg.gpu_config.view_height = 1200;
            app->Init(cfg);
            System::Mouse::Instance()->LockInWindow(true);
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
