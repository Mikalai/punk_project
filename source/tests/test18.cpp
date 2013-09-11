#include "test18.h"

namespace Test18
{
    class TestApp : public Punk::Application
    {
        float m_x;
        float m_y;
        float m_z;
        static const unsigned max_model = 3;
        static const unsigned max_atten = 3;
        Gpu::LightModel m_model[3];
        unsigned m_cur_model;
        Gpu::LightAttenuation m_attenuation[3];
        unsigned m_cur_attent;
        float m_specular;
        bool m_use_texture;
        bool m_use_transparency;

        Virtual::River* m_river;
        Virtual::TerrainMesh* m_terrain;
        Virtual::Material* m_terrain_material;
        Virtual::Material* m_river_material;
    public:
        TestApp()
        {
            m_cur_attent = 0;
            m_cur_model = 2;
            m_model[0] = Gpu::LightModel::PerVertexDiffuse;
            m_model[1] = Gpu::LightModel::PerFragmentDiffuse;
            m_model[2] = Gpu::LightModel::BumpMappingDiffuse;

            m_attenuation[0] = Gpu::LightAttenuation::Constant;
            m_attenuation[1] = Gpu::LightAttenuation::Linear;
            m_attenuation[2] = Gpu::LightAttenuation::Quadratic;

            m_x = 0;
            m_y = 0;
            m_z = 0;

            m_use_texture = true;
            m_use_transparency = false;

            m_specular = 32;
        }

        virtual void OnInit(const Punk::Config&) override
        {
            m_terrain_material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"terrain.material"));
            m_river_material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"river.material"));
            m_river = Cast<Virtual::River*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"river_mesh.river"));
            m_terrain = Cast<Virtual::TerrainMesh*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"terrain_mesh.terrain"));

            //Cast<Virtual::StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"bridge_mesh.static"));

        }

        virtual void OnDestroy() override
        {
            delete m_terrain;
            delete m_river;
            delete m_terrain_material;
            delete m_river_material;
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event)
        {
            m_specular += event->delta;

            if (m_specular < 1)
                m_specular = 1;
        }

        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
            if (event->key == System::PUNK_KEY_A)
            {
                m_cur_attent = (m_cur_attent + 1) % max_atten;
            }
            else if (event->key == System::PUNK_KEY_Z)
            {
                m_cur_attent = (m_cur_attent - 1) % max_atten;
            }
            else if (event->key == System::PUNK_KEY_S)
            {
                m_cur_model = (m_cur_model + 1) % max_model;
            }
            else if (event->key == System::PUNK_KEY_X)
            {
                m_cur_model = (m_cur_model - 1) % max_model;
            }
            else if (event->key == System::PUNK_KEY_T)
            {
                m_use_texture = !m_use_texture;
            }
            else if (event->key == System::PUNK_KEY_B)
            {
                m_use_transparency = !m_use_transparency;
            }
        }

        void DrawTerrain(Gpu::Frame* frame)
        {
            frame->PushAllState();

            Virtual::StaticGeometry* m_geometry = m_terrain->GetGeometry();
            if (!m_geometry)
            {
                m_geometry = Cast<Virtual::StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + m_terrain->GetStaticMeshFilename()));
                m_terrain->SetGeometry(m_geometry);
            }

            if (m_geometry)
            {
                if (!m_geometry->GetGpuCache().IsOnGpu())
                    m_geometry->GetGpuCache().Update(GetVideoDriver());


                for (size_t i = 0; i != m_terrain_material->GetTextureSlotCount(); ++i)
                {
                    Virtual::TextureSlot* slot = m_terrain_material->GetTextureSlot(i);
                    if (!slot->GetGpuCache().IsOnGpu())
                        slot->GetGpuCache().Update(GetVideoDriver());

                    if (m_terrain_material->GetTextureSlot(i)->IsDiffuseMapSlot())
                        frame->SetDiffuseMap(0, m_terrain_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 0);
                    if (m_terrain_material->GetTextureSlot(i)->IsNormalMapSlot())
                        frame->SetNormalMap(m_terrain_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 1);
                }

                frame->SetLightModel(Gpu::LightModel::PerVertexDiffuse);

                frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
                //frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
                //frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
                frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
                frame->Render(m_geometry->GetGpuCache().GetGpuBuffer());
                frame->PopAllState();
            }
        }


        void DrawRiver(Gpu::Frame* frame)
        {
            frame->PushAllState();
            Virtual::StaticGeometry* m_geometry = m_river->GetGeometry();
            if (!m_geometry)
            {
                m_geometry = Cast<Virtual::StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + m_river->GetStaticMeshFilename()));
                m_river->SetGeometry(m_geometry);
            }
            if (m_geometry)
            {
                if (!m_geometry->GetGpuCache().IsOnGpu())
                    m_geometry->GetGpuCache().Update(GetVideoDriver());

                for (size_t i = 0; i != m_river_material->GetTextureSlotCount(); ++i)
                {
                    Virtual::TextureSlot* slot = m_river_material->GetTextureSlot(i);
                    if (!slot->GetGpuCache().IsOnGpu())
                        slot->GetGpuCache().Update(GetVideoDriver());

                    if (m_river_material->GetTextureSlot(i)->IsDiffuseMapSlot())
                        frame->SetDiffuseMap(0, m_river_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 0);
                    if (m_river_material->GetTextureSlot(i)->IsNormalMapSlot())
                        frame->SetNormalMap(m_river_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 1);
                }

                frame->SetTextureMatrix(Math::mat4::CreateTranslate(m_x*0.1, 0, 0));
                frame->SetLightModel(Gpu::LightModel::BumpMappingDiffuse);
                frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
                //frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
                //frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
                frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
                frame->Render(m_geometry->GetGpuCache().GetGpuBuffer());
                frame->PopAllState();
            }
        }

        virtual void OnRender(Gpu::Frame* frame) override
        {

            frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
            frame->EnableDiffuseShading(true);
            frame->EnableTexturing(m_use_texture);

            frame->SetTextureMatrix(Math::mat4::CreateIdentity());
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
            frame->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(1, 1, 1), Math::vec3(0, 0, 0), Math::vec3(0, 0, 1)));

            frame->PushAllState();
            frame->EnableLighting(true);

            frame->SetDiffuseColor(Math::vec4(1,1,1,1));

            frame->Light(0).SetPosition(2, 2, 10);
            frame->Light(0).SetDirection(Math::vec3(-2,-2,-7).Normalize());
            frame->Light(0).SetDiffuseColor(1, 1, 1, 1);
            frame->Light(0).SetLightAttenuation(m_attenuation[m_cur_attent]);
            frame->Light(0).SetLightLinearAttenuation(0.0001);
            frame->Light(0).SetLightQuadricAttenuation(0);
            frame->Light(0).SetType(Gpu::LightType::Point);
            frame->Light(0).SetSpotExponent(m_specular);



            frame->BeginRendering();
            frame->Clear(true, true, true);
            DrawTerrain(frame);
            DrawRiver(frame);

            frame->EndRendering();

            m_x += 0.03f;
            m_y += 0.02f;
            m_z += 0.01f;

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
