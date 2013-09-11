//#include "test21.h"

//namespace Test21
//{
//    class TestApp : public Punk::Application
//    {
//        Scene::SceneGraph* m_scene;
//        Math::vec3 m_view_point;
//        float m_camera_height;
//        Math::mat4 m_projection_matrix;
//        //Math::mat4 m_view_matrix;
//        Virtual::Camera m_camera;

//        Math::vec3 m_camera_move_dir;
//        float m_camera_speed;

//        bool m_move_forward;
//        bool m_move_backward;
//        bool m_move_right;
//        bool m_move_left;

//        Virtual::ArmatureAnimationMixer* m_anim_mixer;

//        Scene::ArmatureNode* m_armature_node;
//    public:
//        TestApp()
//        {
//        }

//        virtual void OnInit(const Punk::Config&) override
//        {
//            m_camera.SetPosition(0, 0, 5);
//            m_camera_height = 5;
//            m_camera_move_dir.Set(0,0,0);
//            m_camera_speed = 1;

//            float width = GetWindow()->GetWidth();
//            float height = GetWindow()->GetHeight();
//            m_projection_matrix = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0);
//            //m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(.2, .2, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));

//            m_scene = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"roman.pmd"));
//            if (!m_scene)
//                return;

//            m_armature_node = As<Scene::ArmatureNode*>(m_scene->Find(L"male_armature_2", true));
//        }

//        virtual void OnDestroy() override
//        {
//            delete m_anim_mixer;
//        }

//        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event) override
//        {
//        }

//        virtual void OnMouseWheel(System::MouseWheelEvent *event)
//        {
//        }

//        virtual void OnMouseMove(System::MouseMoveEvent *event)
//        {
//            m_camera.SetYaw(m_camera.GetYaw() + 1*(event->x - event->x_prev) / (float)GetWindow()->GetWidth());
//            m_camera.SetRoll(m_camera.GetRoll() + 1*(event->y - event->y_prev) / (float)GetWindow()->GetHeight());
//        }

//        virtual void OnResize(System::WindowResizeEvent *event)
//        {
//            float width = GetWindow()->GetWidth();
//            float height = GetWindow()->GetHeight();
//            m_projection_matrix = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0);
//        }

//        void UpdateViewMatrix()
//        {
//            //m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 5, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));
//        }

//        virtual void OnKeyDown(System::KeyDownEvent *event)
//        {
//            switch (event->key)
//            {
//            case System::PUNK_KEY_W:
//                m_move_forward = true;
//                break;
//            case System::PUNK_KEY_S:
//                m_move_backward = true;
//                break;
//            case System::PUNK_KEY_A:
//                m_move_right = true;
//                break;
//            case System::PUNK_KEY_D:
//                m_move_left = true;
//            default:
//                break;
//            }
//        }

//        virtual void OnKeyUp(System::KeyUpEvent *event)
//        {
//            switch (event->key)
//            {
//            case System::PUNK_KEY_W:
//                m_move_forward = false;
//                break;
//            case System::PUNK_KEY_S:
//                m_move_backward = false;
//                break;
//            case System::PUNK_KEY_A:
//                m_move_right = false;
//                break;
//            case System::PUNK_KEY_D:
//                m_move_left = false;
//            default:
//                break;
//            }
//        }

//        virtual void OnIdle(System::IdleEvent *event)
//        {
//            m_camera_move_dir.Set(0,0,0);
//            if (m_move_forward)
//                m_camera_move_dir += m_camera.GetDirection();
//            if (m_move_backward)
//                m_camera_move_dir -= m_camera.GetDirection();
//            if (m_move_left)
//                m_camera_move_dir += m_camera.GetRightVector();
//            if (m_move_right)
//                m_camera_move_dir -= m_camera.GetRightVector();

//            m_camera.SetPosition(m_camera.GetPosition() + m_camera_move_dir.Normalized() * m_camera_speed * event->elapsed_time_s);

//            static float time = 0;
//            m_armature_node->GetArmatureAnimationMixer()->SetTrackTime(time);
//            time += event->elapsed_time_s * 30.0f;

//        }

//        virtual void OnRender(Gpu::Frame* frame) override
//        {
//            frame->PushAllState();

//            frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
//            frame->EnableDiffuseShading(true);
//            frame->EnableTexturing(true);
//            frame->EnableLighting(true);
//            frame->SetViewMatrix(m_camera.GetViewMatrix());
//            frame->SetProjectionMatrix(m_projection_matrix);
//            frame->BeginRendering();
//            frame->Clear(true, true, true);
//            ::Render::Render2 render;
//           // render.SetCamera(&m_camera);
//            //frame->EnableBoundBoxRendering(true);
//            //frame->EnableBoundingSphereRendering(true);
//            //frame->EnableNaviMeshRendering(true);
//            render.RenderScene(m_scene, frame);

//            frame->PushAllState();
//            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//            frame->EnableDepthTest(false);
//            frame->SetPointSize(10);
//            frame->PopAllState();

//            frame->EndRendering();

//            frame->PopAllState();
//        }
//    };

//    void Test::Run()
//    {
//        m_result = true;
//        try
//        {
//            TestApp* app = new TestApp;
//            Punk::Config cfg;
//            cfg.gpu_config.view_width = 800;
//            cfg.gpu_config.view_height = 600;
//            app->Init(cfg);
//            System::Mouse::Instance()->LockInWindow(true);
//            app->GetWindow()->ShowCursor(false);
//            app->Run();
//            delete app;
//        }
//        catch(System::PunkException& e)
//        {
//            out_error() << e.ToString() << std::endl;
//            m_result = false;
//        }
//        catch(std::exception& e)
//        {
//            out_error() << e.what() << std::endl;
//            m_result = false;
//        }
//        catch(...)
//        {
//            m_result = false;
//        }
//    }

//    bool Test::Succeed()
//    {
//        return m_result;
//    }
//}
