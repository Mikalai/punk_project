#include "test7.h"

//
//	Diffuse light
//
namespace Test7
{
	class TestApp : public Punk::Application
	{
		float m_x;
		float m_y;
		float m_z;
		std::unique_ptr<GPU::Renderable> m_renderable;
	public:
		TestApp()
		{
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}

		virtual void OnInit(const Punk::Config&) override
		{
			GPU::RenderableBuilder b(GetVideoDriver());
			b.Begin(GPU::PrimitiveType::QUADS);
			{
				// Front Face
				b.Normal3f( 0.0f, 0.0f, 1.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Point 1 (Front)
				b.Normal3f( 0.0f, 0.0f, 1.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Point 2 (Front)
				b.Normal3f( 0.0f, 0.0f, 1.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Front)
				b.Normal3f( 0.0f, 0.0f, 1.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Point 4 (Front)
				// Back Face
				b.Normal3f( 0.0f, 0.0f,-1.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
				b.Normal3f( 0.0f, 0.0f,-1.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Point 2 (Back)
				b.Normal3f( 0.0f, 0.0f,-1.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Point 3 (Back)
				b.Normal3f( 0.0f, 0.0f,-1.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Point 4 (Back)
				// Top Face
				b.Normal3f( 0.0f, 1.0f, 0.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Point 1 (Top)
				b.Normal3f( 0.0f, 1.0f, 0.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Point 2 (Top)
				b.Normal3f( 0.0f, 1.0f, 0.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Top)
				b.Normal3f( 0.0f, 1.0f, 0.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Point 4 (Top)
				// Bottom Face
				b.Normal3f( 0.0f,-1.0f, 0.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Bottom)
				b.Normal3f( 0.0f,-1.0f, 0.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Point 2 (Bottom)
				b.Normal3f( 0.0f,-1.0f, 0.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Point 3 (Bottom)
				b.Normal3f( 0.0f,-1.0f, 0.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Point 4 (Bottom)
				// Right face
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Point 1 (Right)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Point 2 (Right)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Right)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Point 4 (Right)
				// Left Face
				b.Normal3f(-1.0f, 0.0f, 0.0f); b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Left)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Point 2 (Left)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Point 3 (Left)
				b.Normal3f( 1.0f, 0.0f, 0.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Point 4 (Left)
			}
			b.End();

			m_renderable.reset(b.ToRenderable());

		}

		virtual void OnRender(GPU::Frame* frame) override
		{
			frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
			frame->EnableDiffuseShading(true);
			frame->EnableLighting(true);
			frame->Light(0).SetPosition(0, 0, 0);
			frame->Light(0).SetDiffuseColor(1, 0, 0, 1);
			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->BeginRendering();
			frame->Clear(true, true, true);
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, -5));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
			frame->Render(m_renderable.get());
			frame->EndRendering();

			m_x += 0.0003f;
			m_y += 0.0002f;
			m_z += 0.0004f;

		}
	};

	void Test::Run()
	{
        m_result = true;
		TestApp app;
		try
		{
			app.Init(Punk::Config());
			System::Mouse::Instance()->LockInWindow(false);
			app.Run();
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
