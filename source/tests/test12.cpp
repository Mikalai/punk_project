#include "test12.h"

namespace Test12
{
	class TestApp : public Punk::Application
	{
		GPU::Renderable* m_renderable;
		Math::Frustum m_frustum;
		float m_a;
		float a, b, h;
		float m_rz;
	public:
		TestApp()
		{
			m_renderable = nullptr;
            m_a = Math::PI / 2.0f - 0.01f;
			a = 20;
			b = 20;
			h = 0;
			m_rz = 0;
		}

		virtual void OnInit(const Punk::Config&) override
		{
			m_frustum.Set(Math::PI / 4.0f, 800, 600, 1, 10.0);

			if (m_renderable)
				delete m_renderable;
			if (GetVideoDriver())
			{
				Math::ClipSpace space = Math::BuildClipSpaceFromPoint(
											m_frustum,
											Math::vec3(sin(m_a)*a, h, b*cos(m_a)));
				m_renderable = GPU::AsRenderable(space, GetVideoDriver());
			}
		}

		virtual void OnMouseWheel(System::MouseWheelEvent *event) override
		{
		}

		virtual void OnMouseMove(System::MouseMoveEvent* event) override
		{
			if (event->rightButton)
				m_rz += 0.01f*float(event->x - event->x_prev);
		}

		virtual void OnResize(System::WindowResizeEvent *event) override
		{
        //	m_frustum.Set(Math::PI / 4.0f, event->width, event->height, 1, 10.0);

//			if (m_renderable)
//				delete m_renderable;
//			if (GetVideoDriver())
//				m_renderable = GPU::AsRenderable(m_frustum, GetVideoDriver());
		}

		virtual void OnKeyDown(System::KeyDownEvent *event) override
		{
			if (event->key == System::PUNK_KEY_LEFT)
				m_a -= 0.01;
			else if (event->key == System::PUNK_KEY_RIGHT)
				m_a += 0.01;

			Math::ClipSpace space = Math::BuildClipSpaceFromPoint(
										m_frustum,
										Math::vec3(sin(m_a)*a, h, b*cos(m_a)));
			delete m_renderable;
			Math::ClipSpace space2;
			Math::vec3 v(1,1,0);
			v.Normalize();
			space2.Add(Math::Plane(v[0], v[1], v[2], 5));
			v.Set(-1,1,0);
			v.Normalize();
			space2.Add(Math::Plane(v[0], v[1], v[2], 5));
			space2.Add(Math::Plane(0, 1, 0, 5));
			space2.Add(Math::Plane(0, -1, 0, 5));
			space2.Add(Math::Plane(0, 0, 1, 5));
			space2.Add(Math::Plane(0, 0, -1, 5));
			//m_renderable = GPU::AsRenderable(m_frustum, GetVideoDriver());
			m_renderable = GPU::AsRenderable(space, GetVideoDriver());
		}


		virtual void OnRender(GPU::Frame* frame) override
		{
			frame->SetClearColor(Math::vec4(0.5, 0.5, 0.5, 1));
			frame->EnableDiffuseShading(true);
			frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.1, 100.0));
			frame->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(-50, -50, -50), Math::vec3(0, 0, 0), Math::vec3(0, 1, 0)));
			frame->PushAllState();

			frame->BeginRendering();
			frame->Clear(true, true, true);
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
//			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
//			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_rz));
			frame->Render(m_renderable);
			frame->PopAllState();

			frame->EndRendering();
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
