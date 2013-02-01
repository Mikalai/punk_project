
#include "../../../../system/module.h"
#include "../../gl/module.h"
#include "../../error/module.h"
#include "driver_win32.h"

namespace GPU
{
	namespace OpenGL
	{
		Driver* Driver::m_instance;

		Driver* Driver::Instance()
		{
			if (!m_instance)
				m_instance = new Driver;
			return m_instance;
		}

		void Driver::Destroy()
		{
			delete m_instance;
			m_instance = 0;
		}

		Driver::~Driver()
		{
			Shutdown();
		}

		Driver::Driver()
		{
		}

		void Driver::ReadConfig()
		{
			System::ConfigFile conf;
			conf.Open(System::Window::Instance()->GetTitle());

			if (!conf.ReadOptionInt(L"screen_width", m_width))
			{
				m_width = System::Window::Instance()->GetDesktopWidth();
				conf.WriteOptionInt(L"screen_width", m_width);
			}

			if (!conf.ReadOptionInt(L"screen_height", m_height))
			{
				m_height = System::Window::Instance()->GetDesktopHeight();
				conf.WriteOptionInt(L"screen_height", m_height);
			}

			if (!conf.ReadOptionInt(L"bpp", m_bits_per_pixel))
			{
				m_bits_per_pixel = System::Window::Instance()->GetDesktopBitsPerPixel();
				conf.WriteOptionInt(L"bpp", m_bits_per_pixel);
			}

			if (!conf.ReadOptionInt(L"fullscreen", (int&)m_fullscreen))
			{
				m_fullscreen = false;
				conf.WriteOptionInt(L"fullscreen", (int)m_fullscreen);
			}

			if (!conf.ReadOptionInt(L"refresh_rate", m_refresh_rate))
			{
				m_refresh_rate = System::Window::Instance()->GetDesktopRefreshRate();
				conf.WriteOptionInt(L"refresh_rate", m_refresh_rate);
			}

			conf.Close();
		}

		bool Driver::Start()
		{
			using namespace System;

			ReadConfig();

			out_message() << L"Initializing OpenGL..." << std::endl;

			HDC deviceContext = ::GetDC(*System::Window::Instance());

			SetFullScreen(m_fullscreen);

			int pixelFormat;
			static PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(pfd),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				m_bits_per_pixel,
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				16,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			if (!(pixelFormat = ChoosePixelFormat(deviceContext, &pfd)))
			{
				out_error() << L"Can't choose pixel format" << std::endl;
				return false;
			}

			if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
			{
				out_error() << L"Can't set pixel format" << std::endl;
				return false;
			}

			HGLRC tempContext;
			if ((tempContext = wglCreateContext(deviceContext)) == NULL)
			{
				out_error() << L"Can't create temporary opengl context" << std::endl;
				return false;
			}

			if (!wglMakeCurrent(deviceContext, tempContext))
			{
				out_error() << L"Can't set created context to be current" << std::endl;
				return false;
			}

			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

			int forward = 0;
			int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
			};

			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetProcAddress("wglCreateContextAttribsARB");

			if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
			{
				out_error() << L"Can't create opengl 3.x context" << std::endl;
				return false;
			}

			if (!wglMakeCurrent(deviceContext, m_opengl_context))
			{
				out_error() << L"Can't set opengl 3.x context to be current" << std::endl;
				return false;
			}

			wglDeleteContext(tempContext);

			InitExtensions(this);

			GLint t;

			out_message() << System::string::Format(L"\tRenderer: %s ", System::string((const char*)glGetString(GL_RENDERER)).Data()) << std::endl;
			out_message() << L"\tVendor: " + System::string((const char*)glGetString(GL_VENDOR)) << std::endl;
			out_message() << L"\tVersion: " + System::string((const char*)glGetString(GL_VERSION)) << std::endl;
			out_message() << L"\tGLSL version: " + System::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
			out_message() << System::string::Format(L"\tMax vertex attribs: %d", t) << std::endl;
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
			out_message() << System::string::Format(L"\tMax vertex uniform components: %d", t) << std::endl;
			glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
			out_message() << System::string::Format(L"\tMax varying floats: %d", t) << std::endl;
			glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &t);
			out_message() << L"\tMax 3D texture size: " << t << std::endl;
			glGetIntegerv(GL_MAX_CLIP_DISTANCES, &t);
			out_message() << L"\tMax clip distances: " << t << std::endl;
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &t);
			out_message() << L"\tMax combined texture image units: " << t << std::endl;
			glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &t);
			out_message() << L"\tMax cube map texture size: " << t << std::endl;
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &t);
			out_message() << L"\tMax draw buffers: " << t << std::endl;
			glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &t);
			out_message() << L"\tMax elements indices: " << t << std::endl;
			glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &t);
			out_message() << L"\tMax elements vertices: " << t << std::endl;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);
			out_message() << L"\tMax texture image units in FS: " << t << std::endl;
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &t);
			out_message() << L"\tMax render buffer size: " << t << std::endl;


			wglSwapIntervalEXT(0);

			const unsigned char* sv= glGetString(GL_SHADING_LANGUAGE_VERSION);
			m_shader_version = ((int)(sv[0]-'0'))*100;
			m_shader_version += ((int)(sv[2]-'0'))*10;
			m_shader_version += ((int)(sv[3]-'0'));

			sv = glGetString(GL_VERSION);
			m_opengl_version = ((int)(sv[0]-'0'))*100;
			m_opengl_version += ((int)(sv[2]-'0'))*10;
			m_opengl_version += ((int)(sv[3]-'0'));

			int profile;
			glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
			if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
				out_message() << L"\tCore profile selected" << std::endl;
			if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
				out_message() << L"\tCompatible profile selected" << std::endl;

			SubscribeForSystemMessages();

			return true;
		}

		void Driver::Shutdown()
		{
			out_message() << L"Destroying video driver..." << std::endl;
			ChangeDisplaySettings(NULL, 0);
			wglMakeCurrent(::GetDC(*System::Window::Instance()), NULL);
			wglDeleteContext(m_opengl_context);
			out_message() << L"Video driver destroyed..." << std::endl;
		}

		void Driver::SwapBuffers()
		{
			if (!::SwapBuffers(::GetDC(*System::Window::Instance())))
				out_error() << "Swap buffer failed" << std::endl;
		}

		void* Driver::GetProcAddress(const char* name)
		{
			void* res = wglGetProcAddress(name);
			if (res != 0)
				return res;
			HMODULE lib = LoadLibrary(TEXT("OpenGL32.dll"));
			res = ::GetProcAddress(lib, name);
			FreeLibrary(lib);
			GetLastError();
			return res;
		}

		void Driver::Restart()
		{
			Shutdown();
			Start();
		}

		void Driver::OnResize(System::Event* e)
		{
			System::WindowResizeEvent* event = dynamic_cast<System::WindowResizeEvent*>(e);			
			if (!event)
				throw OpenGLInvalidValueException(L"Can't understand event");
			glViewport(0, 0, event->width, event->height);
		}

		void Driver::SetFullScreen(bool flag)
		{
			m_fullscreen = flag;
			if (m_fullscreen)
			{
				SetWindowLong(*System::Window::Instance(), GWL_STYLE, WS_POPUP);
				SetWindowLong(*System::Window::Instance(), GWL_EXSTYLE, WS_EX_APPWINDOW);

				out_message() << L"Fullscreen mode..." << std::endl;
				DEVMODE mode;
				ZeroMemory(&mode, sizeof(mode));
				mode.dmSize = sizeof(mode);
				mode.dmPelsWidth = m_width;
				mode.dmPelsHeight = m_height;
				mode.dmBitsPerPel = m_bits_per_pixel;
				mode.dmDisplayFrequency = m_refresh_rate;
				mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

				SetWindowPos(*System::Window::Instance(), 0, 0, 0, m_width, m_height, SWP_SHOWWINDOW);

				LONG code;
				if (code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					out_error() << L"Can't change display settings " << std::endl;					
					return;
				}
			}
			else
			{
				SetWindowLong(*System::Window::Instance(), GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLong(*System::Window::Instance(), GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

				out_message() << L"Window mode..." << std::endl;
				System::Window::Instance()->SetPosition(30, 30);
				System::Window::Instance()->SetSize(2*m_width/3, 2*m_height/3);
			}

			ShowWindow(*System::Window::Instance(), SW_SHOW);
			SetFocus(*System::Window::Instance());
		}

		void Driver::OnKeyPress(System::Event* e)
		{
			System::KeyDownEvent* event = dynamic_cast<System::KeyDownEvent*>(e);
			if (!event)
			{
				out_error() << L"Unexpected event recieved" << std::endl;
				return;
			}

			if (event->key == System::PUNK_KEY_ENTER)
			{
				if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_ALT))
					SetFullScreen(!m_fullscreen);
			}
		}

		void Driver::SubscribeForSystemMessages()
		{
			System::EventManager* mgr = System::EventManager::Instance();
			if (!mgr)
			{
				out_error() << L"Unable to get event manager" << std::endl;
				return;
			}

			mgr->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Driver::OnResize));
			mgr->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Driver::OnKeyPress));
		}

		/*RenderTarget* Driver::CreateRenderTarget(RenderTarget::Properties* p)
		{
			switch(p->m_type)
			{
			case RENDER_TARGET_BACK_BUFFER:
				{
					RenderTarget* target = new RenderTargetBackBuffer;
					if (!target->Init(p))
					{
						out_error() << "Can't initialize render target back buffer" << std::endl;
						delete target;
						return 0;
					}
					m_targets.push_back(target);
					return target;
				}
			case RENDER_TARGET_TEXTURE_2D:
				{
					RenderTargetTexture* target = new RenderTargetTexture;				
					if (!target->Init(p))
					{
						out_error() << "Can't initialize render target texture 2d" << std::endl;
						delete target;
						return 0;
					}
					m_targets.push_back(target);
					return target;
				}
			default:
				out_error() << "Can't create render target: " << p->m_type << std::endl;
			}
			return 0;
		}*/
	}
}
