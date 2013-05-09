#include "firsttriangleandquad.h"

class MyAppTestTriangleQuad : public Punk::Application
{    
public:
    MyAppTestTriangleQuad()
    {}

    virtual void OnRender(GPU::Frame* frame) override
    {
        frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
        frame->EnableDiffuseShading(true);
        frame->SetDiffuseColor(Math::vec4(1,1,1,1));

        frame->BeginRendering();
        frame->SetWorldMatrix(Math::mat4::CreateTranslate(-1.5, 0, -6));
        frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.1, 100.0));

        frame->SetDiffuseColor(Math::vec4(1,1,1,1));
        GPU::RenderableBuilder builder(GetVideoDriver());
        builder.Begin(GPU::PrimitiveType::TRIANGLES);
        builder.Vertex3f(0, 1, 0);
        builder.Vertex3f(-1, -1, 0);
        builder.Vertex3f(1, -1, 0);
        builder.End();

        std::unique_ptr<GPU::Renderable> r(builder.ToRenderable());
        frame->Render(r.get());

        frame->SetWorldMatrix(Math::mat4::CreateTranslate(1.5, 0, -6));
        GPU::RenderableBuilder b(GetVideoDriver());
        b.Begin(GPU::PrimitiveType::TRIANGLES);
        b.Vertex3f(-1, 1, 0);
        b.Vertex3f(-1, -1, 0);
        b.Vertex3f(1, -1, 0);

        b.Vertex3f(1, -1, 0);
        b.Vertex3f(1, 1, 0);
        b.Vertex3f(-1, 1, 0);
        b.End();

        std::unique_ptr<GPU::Renderable> r2(b.ToRenderable());
        frame->Render(r2.get());

        frame->EndRendering();

    }
};

void TestTriangleQuad::Run()
{
    MyAppTestTriangleQuad app;
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

bool TestTriangleQuad::Succeed()
{
    return m_result;
}
