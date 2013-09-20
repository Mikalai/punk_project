#include "test17.h"

namespace Test17
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

        Virtual::StaticGeometry* m_geometry;
        Virtual::Material* m_material;
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
            m_material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"bridge_material.material"));
            m_geometry = new Virtual::StaticGeometry;
            m_geometry->SetFilename(L"bridge_mesh.static");
            //Cast<Virtual::StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + L"bridge_mesh.static"));

        }

        virtual void OnDestroy() override
        {
            delete m_geometry;
            delete m_material;
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


        virtual void OnRender(Gpu::Frame* frame) override
        {
            if (!m_geometry->GetGpuCache().IsOnGpu())
                m_geometry->GetGpuCache().Update(GetVideoDriver());

            for (size_t i = 0; i != m_material->GetTextureSlotCount(); ++i)
            {
                Virtual::TextureSlot* slot = m_material->GetTextureSlot(i);
                if (!slot->GetGpuCache().IsOnGpu())
                    slot->GetGpuCache().Update(GetVideoDriver());

                if (m_material->GetTextureSlot(i)->IsDiffuseMapSlot())
                    frame->SetDiffuseMap(0, m_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 0);
                else if (m_material->GetTextureSlot(i)->IsNormalMapSlot())
                    frame->SetNormalMap(m_material->GetTextureSlot(i)->GetGpuCache().GetTexture(), 1);
            }

            frame->SetClearColor(Math::vec4(0, 0, 0, 1));
            frame->EnableDiffuseShading(true);
            frame->EnableTexturing(m_use_texture);                        

            frame->SetTextureMatrix(Math::mat4::CreateIdentity());
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
            frame->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 2, 2), Math::vec3(0, 0, 0), Math::vec3(0, 1, 0)));

            frame->PushAllState();
            frame->EnableLighting(true);

            if (m_use_transparency)
            {
                if (m_use_texture)
                    frame->SetDiffuseColor(Math::vec4(1,1,1,0.5));
                else
                    frame->SetDiffuseColor(Math::vec4(1,0,0,0.5));
            }
            else
            {
                if (m_use_texture)
                    frame->SetDiffuseColor(Math::vec4(1,1,1,1));
                else
                    frame->SetDiffuseColor(Math::vec4(1,0,0,1));
            }

            frame->Light(0).SetPosition(2, 2, 0);
            frame->Light(0).SetDirection(Math::vec3(-2,-2,-7).Normalize());
            frame->Light(0).SetDiffuseColor(1, 1, 1, 1);
            frame->Light(0).SetLightAttenuation(m_attenuation[m_cur_attent]);
            frame->Light(0).SetLightLinearAttenuation(0.1);
            frame->Light(0).SetLightQuadricAttenuation(0.05);
            frame->Light(0).SetType(Gpu::LightType::Spot);
            frame->Light(0).SetSpotExponent(m_specular);

            frame->SetLightModel(m_model[m_cur_model]);


            frame->BeginRendering();
            frame->Clear(true, true, true);
            frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
            frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
            frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
            frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
            frame->Submit(m_geometry->GetGpuCache().GetGpuBuffer());
            frame->PopAllState();

            //frame->SetDiffuseColor(Math::vec4(1,1,1,1));
            //frame->SetWorldMatrix(Math::mat4::CreateIdentity());

            //frame->DrawLine(Math::vec3(1, 1, -2), Math::vec3(0, 0, -7));

            frame->EndRendering();

            m_x += 0.03f;
            m_y += 0.02f;
            m_z += 0.04f;

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
