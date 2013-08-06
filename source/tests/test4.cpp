#include "test4.h"

namespace Test4
{
	class TestApp : public Punk::Application
	{
		float m_tr;
		float m_quad;

		std::unique_ptr<GPU::Renderable> m_rt1;
		std::unique_ptr<GPU::Renderable> m_rt2;

	public:
		TestApp()
		{
			m_tr = 0;
			m_quad = 0;
		}

		void OnInit(const Punk::Config &value) override
		{
			GPU::RenderableBuilder builder(GetVideoDriver());
			builder.Begin(GPU::PrimitiveType::TRIANGLES);
			builder.Color3f(1, 0, 0);
			builder.Vertex3f(0, 1, 0);
			builder.Color3f(0, 1, 0);
			builder.Vertex3f(-1, -1, 0);
			builder.Color3f(0, 0, 1);
			builder.Vertex3f(1, -1, 0);
			builder.End();
			m_rt1.reset(builder.ToRenderable());

			GPU::RenderableBuilder b(GetVideoDriver());
			b.Begin(GPU::PrimitiveType::TRIANGLES);
			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(-1, 1, 0);
			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(-1, -1, 0);
			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(1, -1, 0);

			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(1, -1, 0);
			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(1, 1, 0);
			b.Color3f(0.5, 0.5, 1.0);
			b.Vertex3f(-1, 1, 0);
			b.End();

			m_rt2.reset(b.ToRenderable());
		}

		virtual void OnRender(GPU::Frame* frame) override
		{			
			frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
			frame->Clear(true, true, true);
			frame->EnableDepthTest(true);
			frame->EnableDiffuseShading(true);
			frame->EnablePerVertexColor(true);			
			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->BeginRendering();
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(-1.5, 0, -6));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_tr));
			frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.1, 100.0));

			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->Render(m_rt1.get());

			frame->SetWorldMatrix(Math::mat4::CreateTranslate(1.5, 0, -6));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_quad));

			frame->Render(m_rt2.get());

			frame->EndRendering();

			m_tr += 0.02f;
			m_quad -= 0.015f;

		}
	};

	void Test::Run()
	{
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
