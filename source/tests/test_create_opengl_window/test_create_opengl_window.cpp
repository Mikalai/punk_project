#include "test_create_opengl_window.h"

class MyApp : public Punk::Application
{
public:
    virtual void OnRender(GPU::Frame*) override
    {

    }
};

void CreateOpenGLWindow::Run()
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

bool CreateOpenGLWindow::Succeed()
{
    return m_result;
}
