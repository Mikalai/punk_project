#include "test_clear_buffer.h"

#include "test_clear_buffer.h"

class MyApp : public Punk::Application
{
public:
    void OnRender(GPU::Frame *frame) override
    {
        frame->SetClearColor(Math::vec4(1, 0, 0, 1));
		frame->SetClearDepth(1.0f);

        frame->BeginRendering();
        frame->EndRendering();
    }
};

void TestClearBuffer::Run()
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

bool TestClearBuffer::Succeed()
{
    return m_result;
}

TestClearBuffer::TestClearBuffer()
{
}
