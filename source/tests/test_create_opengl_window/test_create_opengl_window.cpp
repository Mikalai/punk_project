#include "test_create_opengl_window.h"

namespace Test1
{
class MyApp : public Punk::Application
{
public:
    virtual void OnRender(Gpu::Frame*) override
    {

    }
};

void Test::Run()
{
    MyApp app;
    try
    {
        app.Init(Punk::Config());
        System::Mouse::Instance()->LockInWindow(false);
        app.Run();
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
