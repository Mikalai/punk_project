#include "../../../source/punk_engine.h"
#include "enemy.h"

namespace Demo
{
    class Game: public Punk::Application
    {
        Scene::SceneGraph* m_scene;
        Scene::SceneGraph* m_scene_2;
        Virtual::Camera m_camera;
        Math::vec3 m_view_point;
        Math::vec3 m_camera_move;
        float m_camera_height;
        Math::mat4 m_projection_matrix;
        Math::mat4 m_view_matrix;
        std::vector<Scene::Selection> m_selection;
        Math::vec3 m_world_screen_point;
        Math::vec3 c, m_p1, m_p2;
        Scene::Node* m_tower_node;
        Scene::Node* m_sun_node;
        Scene::Node* m_sun_transform;
        float m_mouse_x;
        float m_mouse_y;
        std::vector<Scene::Node*> m_paths;
        std::vector<Enemy*> m_enemy;
        //Scene::ArmatureNode* m_armature_node;
        Scene::Node* m_enemy_visible;

        Gpu::FrameBuffer* m_frame_buffer;
        Gpu::ShadowMapRender* m_shadow_map_render;

        int m_killed_count;
        int m_horde_left;
        int m_max_on_map;
        int m_active_count;
    public:
        Game()
        {
            m_killed_count = 0;
            m_horde_left = 30;
            m_max_on_map = 10;
            m_active_count = 0;
        }

        void OnKill(System::Event* e)
        {
            Enemy* enemy = (Enemy*)e;
            enemy->Activate();
            m_killed_count++;
            m_active_count--;
            if (m_horde_left)
            {
                enemy->Activate();
                m_horde_left--;
            }
        }

        void OnReach(System::Event* e)
        {
            Enemy* enemy = (Enemy*)e;
            m_active_count--;
            if (m_horde_left)
            {
                enemy->Activate();
                m_horde_left--;
            }
        }

        void OnActivate(System::Event* e)
        {
            m_active_count++;
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

            m_scene = Cast<Scene::SceneGraph*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"level_2.pmd"));
            if (!m_scene)
                return;
            m_tower_node = m_scene->Find(L"tower_node_transform", true);
            m_sun_node = m_scene->Find(L"Sun.sun", true);
            m_sun_transform = m_scene->Find(L"Sun_transform", true);
            if (!m_tower_node)
                return;
            auto m1 = Scene::GetGlobalMatrix(m_tower_node);
            auto m2 = Scene::GetGlobalMatrix(m_sun_transform);
            m_scene->Remove(m_tower_node, true);
            // m_sun_node->Add(m_tower_node);
            // m_tower_node->SetLocalMatrix(m2.Inversed()*m1);
            auto res = m_scene->FindAll(L"road_curve", true, false);
            for (auto o : res)
            {
                Scene::Node* n = As<Scene::Node*>(o);
                if (n)
                    m_paths.push_back(n);
            }

            m_enemy_visible = m_scene->Find(L"enemy_transform", true);
            m_scene->Remove(m_enemy_visible, true);
            for (size_t i = 0; i != m_paths.size(); ++i)
            {
                Scene::Node* path_node = m_paths[i];
                AI::CurvePath* path = As<AI::CurvePath*>(path_node->GetData());
                if (!path)
                {
                    path = Cast<AI::CurvePath*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + path_node->GetName()));
                    if (path)
                        path_node->SetData(path);
                }
            }

            //m_armature_node = As<Scene::ArmatureNode*>(m_scene->Find(L"male_armature_2", true));
            //m_paths[0]->SetVisibleData(m_enemy_visible);

            m_frame_buffer = GetVideoDriver()->CreateFrameBuffer(GetWindow()->GetWidth(), GetWindow()->GetHeight());
            //m_depth_buffer = GetVideoDriver()->CreateTexture2D(512, 512, ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT24, ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT, 0, false);
            //m_color_buffer = GetVideoDriver()->CreateTexture2D(512, 512, ImageModule::IMAGE_FORMAT_RGBA, ImageModule::IMAGE_FORMAT_RGBA, 0, false);

            m_shadow_map_render = new Gpu::ShadowMapRender(GetVideoDriver());
        }

        virtual void OnDestroy() override
        {
        }

        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event) override
        {
            Scene::Node* new_tower = m_tower_node->Clone();
            new_tower->SetName("tower_node_transform");
            Math::mat4 g = Scene::GetGlobalMatrix(m_tower_node);
            auto p = Math::mat4::CreateTranslate(g.TranslationPart()).Inversed();
            auto m1 = Math::mat4::CreateTranslate(c) * p * g;
            auto m2 = Scene::GetGlobalMatrix(m_sun_transform);
            Virtual::Transform* transform = new Virtual::Transform;
            transform->Set(m2.Inversed()*m1);
            new_tower->SetData(transform);
            m_sun_node->Add(new_tower);
        }

        Scene::Node* SelectTower(int x, int y)
        {
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            Scene::Selector selector(m_projection_matrix, m_view_matrix, Math::vec2(x, y), Math::vec2(width, height), 5);
            selector.m_check_geometry = false;
            selector.Select(m_scene);
            for (Scene::Selection& s : selector.m_selections)
            {
                Scene::Node* o = As<Scene::Node*>(s.GetObject());
                while (o != nullptr)
                {
                    if (o->GetName().find(L"tower_node_transform") != System::string::npos)
                    {
                        return As<Scene::Node*>(o);
                    }
                    o = As<Scene::Node*>(o->GetOwner());
                }
            }
            return nullptr;
        }

        virtual void OnMouseRightButtonDown(System::MouseRightButtonDownEvent *event) override
        {
            Scene::Node* node = SelectTower(event->x, event->y);
            if (node)
            {
                if (m_scene->Remove(node, true))
                    delete node;
            }
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event)
        {
            m_camera_height += 0.03 * event->delta;
            UpdateViewMatrix();
        }

        virtual void OnMouseMove(System::MouseMoveEvent *event)
        {
            //     m_view_point[0] +override.001 * float(event->x - event->x_prev);
            //    m_view_point[1] +override.001 * float(event->y - event->y_prev);

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

            Math::vec2 p(m_mouse_x, m_mouse_y);
            Math::vec2 s(GetWindow()->GetWidth(), GetWindow()->GetHeight());
            Scene::Selector selector(m_projection_matrix, m_view_matrix, p, s, 5);
            selector.m_check_bounding_box = true;
            selector.Select(m_scene);
            m_selection = selector.m_selections;
            m_world_screen_point = selector.m_world_screen_point;
            if (!m_selection.empty())
            {
                c = m_selection[0].GetPoints()[0];
            }

            m_mouse_x = event->x;
            m_mouse_y = event->y;
        }

        void UpdateViewMatrix()
        {
            m_view_matrix = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 1, m_camera_height) + m_view_point, Math::vec3(0, 0, 0)  + m_view_point, Math::vec3(0, 0, 1));
        }

        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
            if (event->key == System::PUNK_KEY_SPACE)
            {
                m_p1 = m_view_matrix.Inversed() * Math::vec3(0,0,0);
                m_p2 = m_p1 + (m_world_screen_point - m_p1).Normalized() * 5;
            }
        }

        virtual void OnResize(System::WindowResizeEvent *event) override
        {
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            m_projection_matrix = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0);

            Math::PerspectiveDecoder decoder(m_projection_matrix);
            std::cout << "Far z: " << decoder.GetFarZ() << std::endl;
            std::cout << "Near z: " << decoder.GetNearZ() << std::endl;
            std::cout << "Fov x: " << Math::RadToDeg(decoder.GetFovX()) << std::endl;
            std::cout << "Fov y: " << Math::RadToDeg(decoder.GetFovY()) << std::endl;
            std::cout << "Aspect: " << decoder.GetWidthToHeightAspectRatio() << std::endl;

            //m_color_buffer->Resize(event->width, event->height);

           // if (m_frame_buffer->Config()->Width() != event->width && m_frame_buffer->Config()->Height() != event->height)
                m_frame_buffer = GetVideoDriver()->CreateFrameBuffer(event->width, event->height);
        }

        virtual void OnIdle(System::IdleEvent *event)
        {
            if (m_camera_move != Math::vec3())
            {
                m_view_point += m_camera_move * event->elapsed_time_s;
                UpdateViewMatrix();
            }

            for (auto river : Virtual::River::Info.Instances)
            {
                double dt = event->elapsed_time_s;
                auto delta = river->GetFlowSpeed() * river->GetFlowDirection() * dt;
                river->SetStreamPosition(river->GetStreamPosition() + delta);
            }

            for (Virtual::AnimationMixer* mixer : Virtual::AnimationMixer::Info.Instances)
            {
                mixer->SetTrackTime(mixer->GetTrackTime() + event->elapsed_time_s);
            }

            for (auto e : m_enemy)
            {
                e->Update(event->elapsed_time_s);
            }

            static float time = 0;
            //m_armature_node->GetArmatureAnimationMixer()->SetTrackTime(time);
            time += event->elapsed_time_s;

            int t = int(time*1000);
            if (m_horde_left && m_active_count < m_max_on_map)
            {
                if (!m_paths.empty())
                {
                    auto path = m_paths[rand() % m_paths.size()]->GetData();
                    if (path)
                    {
                        Enemy* e = new Enemy;
                        e->OnKilled(System::EventHandler(this, &Game::OnKill));
                        e->OnReached(System::EventHandler(this, &Game::OnReach));
                        e->OnActivate(System::EventHandler(this, &Game::OnActivate));
                        e->SetVisibleData(m_enemy_visible->Clone());
                        e->SetPath(As<AI::CurvePath*>(path));
                        e->Activate();
                        m_enemy.push_back(e);
                        m_horde_left--;
                    }
                }
            }

            //m_camera.SetPosition(m_camera.GetPosition() + m_camera_move);
        }

        virtual void OnRender(Gpu::Frame* frame) override
        {
            frame->PushAllState();
            {

                frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
                frame->EnableDiffuseShading(true);
                frame->EnableTexturing(true);
                frame->EnableLighting(true);
                frame->EnableShadows(false);
                frame->SetViewMatrix(m_view_matrix);
                frame->SetProjectionMatrix(m_projection_matrix);
                frame->EnableDepthRendering(false);
                //frame->SetRenderTarget(m_color_buffer, m_depth_buffer);

                //frame->BeginRendering(m_frame_buffer);
                frame->BeginRendering();
                frame->EnableDepthTest(true);
                //frame->BeginRendering();
                frame->Clear(true, true, false);
                ::Render::Render2 render(GetAsyncParser());
                // render.SetCamera(&m_camera);
                //frame->EnableBoundBoxRendering(true);
                //frame->EnableBoundingSphereRendering(true);
                //frame->EnableNaviMeshRendering(true);
                render.RenderScene(m_scene, frame);
                frame->DrawCircleXY(c.X(), c.Y(), c.Z(), 0.05f);
                frame->DrawText2D(10, GetWindow()->GetHeight() - 30, L"PunkEngine");
                Gpu::LightParameters l;
                l.SetDirection(Math::vec3(0, 1, -1).Normalized());
                l.SetDiffuseColor(1,1,1,1);
                m_shadow_map_render->SetLight(l);
                m_shadow_map_render->SetViewpoint(m_projection_matrix, m_view_matrix);
                m_shadow_map_render->Run(frame);

                frame->EndRendering();
            }
            frame->PopAllState();

//            frame->PushAllState();
//            {
//                frame->EnableDepthTest(true);
//                frame->EnableLighting(false);
//                frame->EnableDiffuseShading(true);
//                frame->EnableTexturing(true);
//                frame->BeginRendering();
//                frame->Clear(true, true, true);
//                frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
//                frame->SetViewMatrix(Math::mat4::CreateIdentity());
//                frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//                frame->SetDiffuseMap0(m_frame_buffer->GetColorTexture());

//                Gpu::RenderableBuilder b(GetVideoDriver());
//                b.Begin(Gpu::PrimitiveType::QUADS);
//                b.TexCoord2f(0,0);
//                b.Vertex3f(-1,-1,0);
//                b.TexCoord2f(0,1);
//                b.Vertex3f(-1,1,0);
//                b.TexCoord2f(1,1);
//                b.Vertex3f(1,1,0);
//                b.TexCoord2f(1,0);
//                b.Vertex3f(1,-1,0);
//                b.End();
//                frame->Render(b.ToRenderable(), true);
//                frame->EndRendering();
//            }
//            frame->PopAllState();

        }
    };
}

int main()
{
    try
    {
        Demo::Game* app = new Demo::Game;
        Punk::Config cfg;
        cfg.gpu_config.view_width = 1920;
        cfg.gpu_config.view_height = 1200;
        cfg.gpu_config.fullscreen = false;
        app->Init(cfg);
        System::Mouse::Instance()->LockInWindow(false);
        app->Run();
        delete app;
    }
    catch(System::PunkException& e)
    {
        std::cout << "Error: " << e.ToString() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown error" << std::endl;
    }
}

//            frame->PushAllState();
//            frame->SetWorldMatrix(Math::mat4::CreateIdentity());
//            frame->EnableDepthTest(false);
//            frame->SetPointSize(10);
//            frame->DrawPoint(m_world_screen_point);
//            frame->EnableDepthTest(true);
//            frame->DrawLine(m_p1, m_p2);
//            for (Scene::Selection& s : m_selection)
//            {
//                if (s.GetType() == Scene::SelectionType::Geometry)
//                    frame->SetDiffuseColor(1, 0, 0, 1);
//                if (s.GetType() == Scene::SelectionType::BoundingBox)
//                    frame->SetDiffuseColor(0, 1, 0, 1);
//                if (s.GetType() == Scene::SelectionType::BoundingSphere)
//                    continue;
//                for (auto p : s.GetPoints())
//                {
//                    frame->DrawPoint(p);
//                }
//            }

////            if (!m_paths.empty())
////            {
////                static float t override;
////                for (size_t i = 0; i != m_paths.size(); ++i)
////                {zz
////                    Scene::PathNode* path_node = m_paths[i];
////                    AI::CurvePath* path = path_node->GetCurvePath();
////                    if (path)
////                    {
////                        frame->DrawPoint(Scene::GetGlobalMatrix(path_node) * path->At(t));
////                        if (t >= 1)
////                            t override;

////                        auto v = path->At(0);
////                        auto vv = path->At(1);
////                        v = v;
////                    }
////                    else
////                    {
////                        path = Cast<AI::CurvePath*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + path_node->GetStorageName()));
////                        if (path)
////                            path_node->SetCurvePath(path);
////                    }
////                }
////                t +override.01;
////            }
//            frame->PopAllState();
