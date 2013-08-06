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
        Math::vec3 c;
        Scene::TransformNode* m_tower_node;
        Scene::SunNode* m_sun_node;
        Scene::TransformNode* m_sun_transform;        
    public:
        TestApp()
        {
        }

        virtual void OnInit(const Punk::Config&) override
        {
            m_camera.SetPosition(3, 3, 3);
            m_camera.SetYawRollPitch(0, 0, -0.3);
            m_camera_height = 1;

            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            m_projection_matrix = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0);
            m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(.2, .2, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));

            m_scene = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"level_1.pmd"));
            if (!m_scene)
                return;
            m_tower_node = Cast<Scene::TransformNode*>(m_scene->Find(L"tower_node_transform", true));
            m_sun_node = Cast<Scene::SunNode*>(m_scene->Find(L"Sun", true));
            m_sun_transform = Cast<Scene::TransformNode*>(m_scene->Find(L"Sun_transform", true));
            if (!m_tower_node)
                return;
            auto m1 = m_tower_node->GetGlobalMatrix();
            auto m2 = m_sun_transform->GetGlobalMatrix();
            m_scene->Remove(m_tower_node);
            m_sun_node->Add(m_tower_node);
            m_tower_node->SetLocalMatrix(m2.Inversed()*m1);
        }

        virtual void OnDestroy() override
        {
        }

        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event) override
        {
            Scene::TransformNode* new_tower = As<Scene::TransformNode*>(m_tower_node->Clone());
            Math::mat4 g = m_tower_node->GetGlobalMatrix();
            auto p = Math::mat4::CreateTranslate(g.TranslationPart()).Inversed();
            auto m1 = Math::mat4::CreateTranslate(c) * p * g;
            auto m2 = m_sun_transform->GetGlobalMatrix();
            new_tower->SetLocalMatrix(m2.Inversed()*m1);

            m_sun_node->Add(new_tower);
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event)
        {
            m_camera_height += 0.1 * event->delta;            
            UpdateViewMatrix();
        }

        virtual void OnMouseMove(System::MouseMoveEvent *event)
        {
       //     m_view_point[0] += 0.001 * float(event->x - event->x_prev);
        //    m_view_point[1] += 0.001 * float(event->y - event->y_prev);

            float m_camera_speed = 0.1;
            m_camera_move.Set(0,0,0);
            if (event->x < GetWindow()->GetWidth() / 10)
                m_camera_move[0] = m_camera_speed;
            if (event->x > GetWindow()->GetWidth() / 10 * 9)
                m_camera_move[0] = -m_camera_speed;
            if (event->y < GetWindow()->GetHeight() / 10)
                m_camera_move[1] = m_camera_speed;
            if (event->y > GetWindow()->GetHeight() / 10 * 9)
                m_camera_move[1] = -m_camera_speed;
            m_camera_move.Normalize();
            UpdateViewMatrix();

            Math::vec2 p(event->x, event->y);
            Math::vec2 s(GetWindow()->GetWidth(), GetWindow()->GetHeight());
            Scene::Selector selector(m_projection_matrix, m_view_matrix, p, s, 100.0f);
            selector.Select(m_scene);
            m_selection = selector.m_selections;
            m_world_screen_point = selector.m_world_screen_point;
            if (!m_selection.empty())
            {
                c = m_selection[0].GetPoints()[0];
            }
        }

        void UpdateViewMatrix()
        {
            m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 1, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));
        }

        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
        }

        virtual void OnIdle(System::IdleEvent *event)
        {
            std::cout << "Something happens " << event->elapsed_time_s << std::endl;
            Virtual::River* river = Virtual::River::find(L"river_mesh");
            if (river)
            {
                double dt = event->elapsed_time_s;
                auto delta = river->GetFlowSpeed() * river->GetFlowDirection() * dt;
                river->SetStreamPosition(river->GetStreamPosition() + delta);
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
            //frame->EnableBoundBoxRendering(true);
            //frame->EnableBoundingSphereRendering(true);
            //frame->EnableNaviMeshRendering(true);
            render.RenderScene(m_scene, frame);
            frame->DrawCircleXY(c.X(), c.Y(), c.Z(), 0.05f);

            frame->PushAllState();
            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
            frame->EnableDepthTest(false);
            frame->SetPointSize(10);
            frame->DrawPoint(m_world_screen_point);
            for (Scene::Selection& s : m_selection)
            {                               
                if (s.GetType() == Scene::SelectionType::Geometry)
                    frame->SetDiffuseColor(1, 0, 0, 1);
                if (s.GetType() == Scene::SelectionType::BoundingBox)
                    frame->SetDiffuseColor(0, 1, 0, 1);
                if (s.GetType() == Scene::SelectionType::BoundingSphere)
                    continue;
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
        m_result = true;
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
        catch(std::exception& e)
        {
            out_error() << e.what() << std::endl;
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
