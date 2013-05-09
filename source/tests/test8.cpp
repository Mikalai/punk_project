#include "test8.h"

//
//	Per fragment lighting
//
namespace Test8
{
	class TestApp : public Punk::Application
	{
		float m_x;
		float m_y;
		float m_z;
		std::unique_ptr<GPU::Renderable> m_renderable;
		static const unsigned max_model = 2;
		static const unsigned max_atten = 3;
		GPU::LightModel m_model[2];
		unsigned m_cur_model;
		GPU::LightAttenuation m_attenuation[3];
		unsigned m_cur_attent;
		float m_specular;
	public:
		TestApp()
		{
			m_cur_attent = 0;
			m_cur_model = 1;
			m_model[0] = GPU::LightModel::PerVertexDiffuse;
			m_model[1] = GPU::LightModel::PerFragmentDiffuse;

			m_attenuation[0] = GPU::LightAttenuation::Constant;
			m_attenuation[1] = GPU::LightAttenuation::Linear;
			m_attenuation[2] = GPU::LightAttenuation::Quadratic;

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
				b.Normal3f(-1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 0.0f); b.Vertex3f(-1.0f, -1.0f,  1.0f);  // Point 2 (Left)
				b.Normal3f(-1.0f, 0.0f, 0.0f); b.TexCoord2f(1.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f,  1.0f);  // Point 3 (Left)
				b.Normal3f(-1.0f, 0.0f, 0.0f); b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f,  1.0f, -1.0f);  // Point 4 (Left)
			}
			b.End();

			m_renderable.reset(b.ToRenderable());

		}

		virtual void OnMouseWheel(System::MouseWheelEvent *event)
		{
			m_specular += event->delta;

			if (m_specular < 1)
				m_specular = 1;
		}

		virtual void OnKeyDown(System::KeyDownEvent *event)
		{
			if (event->key == System::PUNK_KEY_A)
			{
				m_cur_attent = (m_cur_attent + 1) % max_atten;
			}
			else if (event->key == System::PUNK_KEY_Z)
			{
				m_cur_attent = (m_cur_attent - 1) % max_atten;
			}
			else if (event->key == System::PUNK_KEY_S)
			{
				m_cur_model = (m_cur_model + 1) % max_model;
			}
			else if (event->key == System::PUNK_KEY_X)
			{
				m_cur_model = (m_cur_model - 1) % max_model;
			}
		}


		virtual void OnRender(GPU::Frame* frame) override
		{
			frame->SetClearColor(Math::vec4(0.7, .7, .7, 1));
			frame->EnableDiffuseShading(true);
			frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.1, 100.0));
			frame->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(-1, -2, 0), Math::vec3(0, 0, -7), Math::vec3(0, 1, 0)));

			frame->PushState();
			frame->EnableLighting(true);
			frame->Light(0).SetPosition(2, 2, 0);
			frame->Light(0).SetDirection(Math::vec3(-2,-2,-7).Normalize());
			frame->Light(0).SetDiffuseColor(1, 0, 0, 1);			
			frame->Light(0).SetLightAttenuation(m_attenuation[m_cur_attent]);
			frame->Light(0).SetLightLinearAttenuation(0.1);
			frame->Light(0).SetLightQuadricAttenuation(0.05);
			frame->Light(0).SetType(GPU::LightType::Spot);			
			frame->Light(0).SetSpotExponent(m_specular);

			frame->SetDiffuseColor(Math::vec4(1,1,1,1));

			frame->SetLightModel(m_model[m_cur_model]);


			frame->BeginRendering();
			frame->Clear(true, true, true);			
			frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, -7));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, m_x));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, m_y));
			frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 0, 1, m_z));
			frame->Render(m_renderable.get());
			frame->PopState();

			frame->SetDiffuseColor(Math::vec4(1,1,1,1));
			frame->SetWorldMatrix(Math::mat4::CreateIdentity());

			frame->DrawLine(Math::vec3(1, 1, -2), Math::vec3(0, 0, -7));

			frame->EndRendering();

			m_x += 0.0003f;
			m_y += 0.0002f;
			m_z += 0.0004f;

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
