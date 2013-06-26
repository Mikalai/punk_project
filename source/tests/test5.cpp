#include "test5.h"

namespace Test5
{
	class TestApp : public Punk::Application
	{
		float m_tr;
		float m_quad;

	public:
		TestApp()
		{
			m_tr = 0;
			m_quad = 0;
		}

		virtual void OnRender(GPU::Frame* frame) override
		{
			frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
			frame->EnableDiffuseShading(true);
			frame->EnablePerVertexColor(true);
			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->BeginRendering();
			frame->Clear(true, true, true);
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(-1.5, 0, -6));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_tr));
            float width = frame->GetVideoDriver()->GetWindow()->GetWidth();
            float height = frame->GetVideoDriver()->GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));

			frame->SetDiffuseColor(Math::vec4(1,1,1,1));
			GPU::RenderableBuilder builder(GetVideoDriver());
			builder.Begin(GPU::PrimitiveType::TRIANGLES);
			{
				builder.Color3f(1.0f,0.0f,0.0f);          // Red
				builder.Vertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
				builder.Color3f(0.0f,1.0f,0.0f);          // Green
				builder.Vertex3f(-1.0f,-1.0f, 1.0f);          // Left Of Triangle (Front)
				builder.Color3f(0.0f,0.0f,1.0f);          // Blue
				builder.Vertex3f( 1.0f,-1.0f, 1.0f);          // Right Of Triangle (Front)			builder.End();

				builder.Color3f(1.0f,0.0f,0.0f);          // Red
				builder.Vertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
				builder.Color3f(0.0f,0.0f,1.0f);          // Blue
				builder.Vertex3f( 1.0f,-1.0f, 1.0f);          // Left Of Triangle (Right)
				builder.Color3f(0.0f,1.0f,0.0f);          // Green
				builder.Vertex3f( 1.0f,-1.0f, -1.0f);         // Right Of Triangle (Right)

				builder.Color3f(1.0f,0.0f,0.0f);          // Red
				builder.Vertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
				builder.Color3f(0.0f,1.0f,0.0f);          // Green
				builder.Vertex3f( 1.0f,-1.0f, -1.0f);         // Left Of Triangle (Back)
				builder.Color3f(0.0f,0.0f,1.0f);          // Blue
				builder.Vertex3f(-1.0f,-1.0f, -1.0f);         // Right Of Triangle (Back)

				builder.Color3f(1.0f,0.0f,0.0f);          // Red
				builder.Vertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
				builder.Color3f(0.0f,0.0f,1.0f);          // Blue
				builder.Vertex3f(-1.0f,-1.0f,-1.0f);          // Left Of Triangle (Left)
				builder.Color3f(0.0f,1.0f,0.0f);          // Green
				builder.Vertex3f(-1.0f,-1.0f, 1.0f);          // Right Of Triangle (Left)
			}
			builder.End();

			std::unique_ptr<GPU::Renderable> r(builder.ToRenderable());
			frame->Render(r.get());

			frame->SetWorldMatrix(Math::mat4::CreateTranslate(1.5, 0, -6));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_quad));
			GPU::RenderableBuilder b(GetVideoDriver());
			b.Begin(GPU::PrimitiveType::QUADS);
			{
				b.Color3f(0.0f,1.0f,0.0f);          // Set The Color To Green
				b.Vertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
				b.Color3f(0.0f,1.0f,0.0f);          // Set The Color To Green
				b.Vertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
				b.Color3f(0.0f,1.0f,0.0f);          // Set The Color To Green
				b.Vertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
				b.Color3f(0.0f,1.0f,0.0f);          // Set The Color To Green
				b.Vertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)

				b.Color3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
				b.Vertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
				b.Color3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
				b.Vertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
				b.Color3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
				b.Vertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
				b.Color3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
				b.Vertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)

				b.Color3f(1.0f,0.0f,0.0f);          // Set The Color To Red
				b.Vertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
				b.Color3f(1.0f,0.0f,0.0f);          // Set The Color To Red
				b.Vertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
				b.Color3f(1.0f,0.0f,0.0f);          // Set The Color To Red
				b.Vertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
				b.Color3f(1.0f,0.0f,0.0f);          // Set The Color To Red
				b.Vertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)

				b.Color3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
				b.Vertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
				b.Color3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
				b.Vertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
				b.Color3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
				b.Vertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
				b.Color3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
				b.Vertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back)

				b.Color3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
				b.Vertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
				b.Color3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
				b.Vertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
				b.Color3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
				b.Vertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
				b.Color3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
				b.Vertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)

				b.Color3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
				b.Vertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
				b.Color3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
				b.Vertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
				b.Color3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
				b.Vertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
				b.Color3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
				b.Vertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)
			}
			b.End();

			std::unique_ptr<GPU::Renderable> r2(b.ToRenderable());
			frame->Render(r2.get());

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
