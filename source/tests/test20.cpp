#include "test20.h"

namespace Test20
{
    class TestApp : public Punk::Application
    {
    public:
        TestApp()
        {
        }

        virtual void OnInit(const Punk::Config&) override
        {
            ImageModule::Importer imp;
            std::unique_ptr<ImageModule::Image> image(imp.LoadAnyImage(System::Environment::Instance()->GetTextureFolder() + L"146b809b.tif"));

            std::cout << "Image " << image.get() << std::endl;
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
