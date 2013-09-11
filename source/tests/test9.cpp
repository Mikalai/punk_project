#include "test9.h"

//
//	Per fragment lighting
//
namespace Test9
{
	class TestApp : public Punk::Application
	{
		float m_x;
		float m_y;
		float m_z;
		std::unique_ptr<Gpu::Renderable> m_renderable;
		std::unique_ptr<Gpu::Texture2D> m_texture;
		static const int c_num_particles = 50;
		bool m_twinkle;
		bool m_t;

		typedef struct                          // Create A Structure For Star
		{
			int r, g, b;                        // Stars Color
			float dist;                       // Stars Distance From Center
			float angle;                      // Stars Current Anb.e
		}
		stars;                              // Structures Name Is Stars
		stars star[c_num_particles];                        // Make 'star' Array Of 'num' Using Info From The Structure 'stars'

		float zoom;
		float tilt;
		float spin;

	public:
		TestApp()
		{
			zoom = -15.0f;                        // Viewing Distance Away From Stars
			tilt = 90.0f;                     // Tilt The View
			spin = 0;                           // Spin Twinkling Stars
			m_twinkle = false;
		}

        virtual void OnDestroy() override
        {
            m_renderable.reset(nullptr);
            m_texture.reset(nullptr);
        }

		virtual void OnInit(const Punk::Config&) override
		{
			Gpu::RenderableBuilder b(GetVideoDriver());
			b.Begin(Gpu::PrimitiveType::QUADS);
			{
				// Front Face
				b.TexCoord2f(0.0f, 0.0f); b.Vertex3f(-1.0f,-1.0f, 0.0f);
				b.TexCoord2f(1.0f, 0.0f); b.Vertex3f( 1.0f,-1.0f, 0.0f);
				b.TexCoord2f(1.0f, 1.0f); b.Vertex3f( 1.0f, 1.0f, 0.0f);
				b.TexCoord2f(0.0f, 1.0f); b.Vertex3f(-1.0f, 1.0f, 0.0f);
			}
			b.End();

			m_renderable.reset(b.ToRenderable());

			ImageModule::Importer importer;
			std::unique_ptr<ImageModule::Image> image(importer.LoadAnyImage(System::Environment::Instance()->GetTextureFolder() + L"Star.png"));
            //m_texture.reset(GetVideoDriver()->CreateTexture2D(*image, ImageModule::ImageFormat::IMAGE_FORMAT_RGBA, true));
            m_texture.reset(GetVideoDriver()->CreateTexture2D(image->ToRGBA(), true));

			for (int loop=0; loop < c_num_particles; loop++)               // Create A Loop That Goes Through All The Stars
			{
				star[loop].angle=0.0f;              // Start All The Stars At Angle Zero
				star[loop].dist=(float(loop)/c_num_particles)*5.0f;     // Calculate Distance From The Center
				star[loop].r=rand()%256;            // Give star[loop] A Random Red Intensity
				star[loop].g=rand()%256;            // Give star[loop] A Random Green Intensity
				star[loop].b=rand()%256;            // Give star[loop] A Random Blue Intensity
			}

		}

		virtual void OnKeyDown(System::KeyDownEvent *event)
		{
			if (event->key == System::PUNK_KEY_T)
			{
				m_t = true;
				m_twinkle = !m_twinkle;
			}
		}

		virtual void OnKeyUp(System::KeyUpEvent *event)
		{
			if (event->key == System::PUNK_KEY_T)
			{
				m_t = false;
			}
		}


		virtual void OnRender(Gpu::Frame* frame) override
		{
            frame->SetClearColor(0, 0, 0, 0.5f);			
			frame->EnableTexturing(true);
			frame->EnableDiffuseShading(true);
			frame->EnableBlending(true);
            frame->EnableDepthTest(false);
            frame->SetBlendColor(1,1,1,1);
			frame->SetBlendFunc(Gpu::BlendFunction::SourceAlpha, Gpu::BlendFunction::One);
            frame->SetDiffuseMap(0, m_texture.get(), 0);
            float width = GetWindow()->GetWidth();
            float height = GetWindow()->GetHeight();
            frame->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, width, height, 0.1, 100.0));
			frame->BeginRendering();
            frame->Clear(true, true, true);
			for (int i = 0; i < c_num_particles; ++i)
			{
				float DegToRad = Math::PI / 180.0f;
				frame->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, zoom));
				frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, tilt*DegToRad));
				frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, star[i].angle*DegToRad));
				frame->MultWorldMatrix(Math::mat4::CreateTranslate(star[i].dist, 0, 0));
				frame->MultWorldMatrix(Math::mat4::CreateRotation(0, 1, 0, -star[i].angle*DegToRad));
				frame->MultWorldMatrix(Math::mat4::CreateRotation(1, 0, 0, -tilt*DegToRad));
				if (m_twinkle)
				{
					// Assign A Color Using Bytes
					frame->SetDiffuseColor(star[(c_num_particles-i)-1].r / 255.0f,
							star[(c_num_particles-i)-1].g / 255.0f,
							star[(c_num_particles-i)-1].b / 255.0f, 1.0f);
					frame->Render(m_renderable.get());
				}
				frame->MultWorldMatrix(Math::mat4::CreateRotation(0.0f,0.0f,1.0f, spin*DegToRad));
				// Assign A Color Using Bytes
				frame->SetDiffuseColor(star[i].r / 255.0f,
									   star[i].g / 255.0f,
									   star[i].b / 255.0f, 1.0f);
				frame->Render(m_renderable.get());

				spin += 0.01f;                    // Used To Spin The Stars
				star[i].angle += float(i)/c_num_particles;      // Changes The Angle Of A Star
				star[i].dist -= 0.01f;             // Changes The Distance Of A Star

				if (star[i].dist < 0.0f)            // Is The Star In The Middle Yet
				{
					star[i].dist += 5.0f;          // Move The Star 5 Units From The Center
					star[i].r = rand() % 256;        // Give It A New Red Value
					star[i].g = rand() % 256;        // Give It A New Green Value
					star[i].b = rand() % 256;        // Give It A New Blue Value
				}
			}
			frame->EndRendering();
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
