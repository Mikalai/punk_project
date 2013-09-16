#include "test23.h"

namespace Test23
{
    class TestApp : public Punk::ViewerApplication
    {
        static const unsigned max_model = 3;
        static const unsigned max_atten = 3;
        Gpu::LightModel m_model[3];
        unsigned m_cur_model;
        Gpu::LightAttenuation m_attenuation[3];
        unsigned m_cur_attent;
        float m_specular;
        bool m_use_texture;
        bool m_use_transparency;
        Virtual::StaticGeometry* m_geom;

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

            m_use_texture = true;
            m_use_transparency = false;

            m_specular = 32;
        }

        virtual void OnInit(const Punk::Config&) override
        {
            m_geom = Cast<Virtual::StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder()
                                                                           + L"Suzanne.static"));
            if (m_geom)
            {
                m_geom->GetGpuCache().Update(GetVideoDriver());
            }
        }

        virtual void OnDestroy() override
        {
            delete m_geom;
        }

        virtual void OnMouseWheel(System::MouseWheelEvent *event)
        {
            m_specular += event->delta;

            if (m_specular < 1)
                m_specular = 1;
        }

        void ChangeAttenuationModel(System::Event* e)
        {
            m_cur_attent = (m_cur_attent + 1) % max_atten;
        }



        virtual void OnKeyDown(System::KeyDownEvent *event)
        {
            if (event->key == System::PUNK_KEY_A)
            {

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

            frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
            frame->EnableDiffuseShading(true);
            frame->EnableSpecularShading(true);
            frame->EnableTexturing(false);

            frame->SetTextureMatrix(Math::mat4::CreateIdentity());
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
            frame->SetViewMatrix(GetViewMatrix());

            frame->PushAllState();
            frame->EnableLighting(true);

            frame->SetSpecularFactor(128);
            frame->SetDiffuseColor(Math::vec4(1,1,1,1));            

            frame->Light(0).Enable();
            frame->Light(0).SetPosition(2, 2, 10);
            frame->Light(0).SetDirection(Math::vec3(-2,-2,-7).Normalize());
            frame->Light(0).SetDiffuseColor(1, 1, 1, 1);
            frame->Light(0).SetLightAttenuation(m_attenuation[m_cur_attent]);
            frame->Light(0).SetLightLinearAttenuation(0.0001);
            frame->Light(0).SetLightQuadricAttenuation(0);
            frame->Light(0).SetType(Gpu::LightType::Point);
            frame->Light(0).SetSpotExponent(m_specular);
            frame->SetLightModel(Gpu::LightModel::PerFragmentDiffuse);

            frame->BeginRendering();
            frame->Clear(true, true, true);
            frame->Render(m_geom->GetGpuCache().GetGpuBuffer());
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

