#include "test6.h"

namespace Test6
{
	class TestApp : public Punk::Application
	{
		float m_x;
		float m_y;
		float m_z;
		std::unique_ptr<Gpu::Texture2D> m_texture;
		std::unique_ptr<Gpu::Renderable> m_renderable;
	public:
		TestApp()
		{
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}

        ~TestApp()
        {}

        virtual void OnDestroy() override
        {
            m_texture.reset(0);
            m_renderable.reset(0);
        }

		virtual void OnInit(const Punk::Config&) override
		{		
			Gpu::RenderableBuilder b(GetVideoDriver());
			b.Begin(Gpu::PrimitiveType::QUADS);
			{
				// Front Face
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
				// Back Face
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
				// Top Face
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
				// Bottom Face
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
				// Right face
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
				// Left Face
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
			}
			b.End();

			m_renderable.reset(b.ToRenderable());

			m_texture.reset(GetVideoDriver()->CreateTexture2D(System::Environment::Instance()->GetTextureFolder() + L"pahonia.png", true));
		}

		virtual void OnRender(Gpu::Frame* frame) override
		{
			frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
			frame->EnableDiffuseShading(true);
			frame->EnablePerVertexColor(true);
			frame->EnableTexturing(true);
			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->BeginRendering();
			frame->Clear(true, true, true);
            frame->SetDiffuseMap(0, m_texture.get(), 0);
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, -5));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
			frame->Submit(m_renderable.get());
			frame->EndRendering();

			m_x += 0.0003f;
			m_y += 0.0002f;
			m_z += 0.0004f;

		}

        void WndOnResizeEvent(System::WindowResizeEvent *) override
		{

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
