
#include "../../../../system/module.h"
#include "../../gl/module.h"
#include "../../error/module.h"
#include "driver_win32.h"

namespace GPU
{
	namespace OpenGL
	{

		Driver::~Driver()
		{
			Shutdown();
		}

		Driver::Driver()
		{
		}

		bool Driver::Start(const DriverDesc& desc)
		{
			m_desc = desc;

			out_message() << L"Initializing OpenGL..." << std::endl;

			HDC deviceContext = ::GetDC((*m_desc.window));

			SetFullScreen(m_desc.config.fullscreen);

			int pixelFormat;
			static PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(pfd),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				m_desc.config.bits_per_pixel,
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

			m_desc.event_manager->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Driver::OnResize));
			m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Driver::OnKeyDown));

			return true;
		}

		void Driver::Shutdown()
		{
			out_message() << L"Destroying video driver..." << std::endl;
			ChangeDisplaySettings(NULL, 0);
			wglMakeCurrent(::GetDC(*m_desc.window), NULL);
			wglDeleteContext(m_opengl_context);
			out_message() << L"Video driver destroyed..." << std::endl;
		}

		void Driver::SwapBuffers()
		{
			if (!::SwapBuffers(::GetDC(*m_desc.window)))
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
			Start(m_desc);
		}

		void Driver::SetFullScreen(bool flag)
		{
			m_desc.config.fullscreen = flag;
			if (flag)
			{
				SetWindowLong(*m_desc.window, GWL_STYLE, WS_POPUP);
				SetWindowLong(*m_desc.window, GWL_EXSTYLE, WS_EX_APPWINDOW);

				out_message() << L"Fullscreen mode..." << std::endl;
				DEVMODE mode;
				ZeroMemory(&mode, sizeof(mode));
				mode.dmSize = sizeof(mode);
				mode.dmPelsWidth = m_desc.config.view_width;
				mode.dmPelsHeight = m_desc.config.view_height;
				mode.dmBitsPerPel = m_desc.config.bits_per_pixel;
				mode.dmDisplayFrequency = m_desc.config.refresh_rate;
				mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

				SetWindowPos(*m_desc.window, 0, 0, 0, m_desc.config.view_width, m_desc.config.view_height, SWP_SHOWWINDOW);

				LONG code;
				if (code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					out_error() << L"Can't change display settings " << std::endl;					
					return;
				}
			}
			else
			{
				SetWindowLong(*m_desc.window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLong(*m_desc.window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

				out_message() << L"Window mode..." << std::endl;
				m_desc.window->SetPosition(m_desc.config.view_left, m_desc.config.view_top);
				m_desc.window->SetSize(m_desc.config.view_width, m_desc.config.view_height);
			}

			ShowWindow(*m_desc.window, SW_SHOW);
			SetFocus(*m_desc.window);
		}

		void Driver::OnKeyDown(System::Event* e)
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
					SetFullScreen(!m_desc.config.fullscreen);
			}
		}

		void Driver::OnResize(System::Event* e)
		{
			System::WindowResizeEvent* event = dynamic_cast<System::WindowResizeEvent*>(e);			
			if (!event)
				throw OpenGLInvalidValueException(L"Can't understand event");
			glViewport(0, 0, event->width, event->height);
		}
	}
}
