#include "driver.h"
#include "../system/window.h"

namespace OpenGL
{
	void Driver::Shutdown()
	{
	}

	void Driver::Restart()
	{
		Shutdown();
		Start();
	}

	void Driver::Init()
	{
		Singletone<Logger>::Get()->WriteMessage(L"Initializing OpenGL...");

		m_parameters.deviceContext = ::GetDC(*System::Window::Instance());

		if (m_parameters.fullScreen)
		{
			System::Logger::Instance()->WriteMessage(L"Fullscreen mode...");
			DEVMODE mode;
			ZeroMemory(&mode, sizeof(mode));
			mode.dmSize = sizeof(mode);
			mode.dmPelsWidth = m_parameters.width;
			mode.dmPelsHeight = m_parameters.height;
			mode.dmBitsPerPel = m_parameters.bitsPerPixel;
			mode.dmDisplayFrequency = m_parameters.refreshRate;
			mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

			MoveWindow(m_parameters.window, 0, 0, m_parameters.width, m_parameters.height, TRUE);

			if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				throw System::SystemError(L"Can't change display settings" + LOG_LOCATION_STRING);					
			}
		}
		else
		{
			System::Logger::Instance()->WriteMessage(L"Window mode...");
			RECT r;
			r.left = 100;
			r.right = m_parameters.width;
			r.top = 100;
			r.bottom = m_parameters.height;
			AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);

			MoveWindow(m_parameters.window, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
		}

		if (m_parameters.fullScreen)
		{
			SetWindowLong(m_parameters.window, GWL_STYLE, WS_POPUP);
			SetWindowLong(m_parameters.window, GWL_EXSTYLE, WS_EX_APPWINDOW);
		}
		else
		{
			SetWindowLong(m_parameters.window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowLong(m_parameters.window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		}

		ShowWindow(m_parameters.window, SW_SHOW);
		SetFocus(m_parameters.window);


		int pixelFormat;
		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(pfd),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			m_parameters.bitsPerPixel,
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

		if (!(pixelFormat = ChoosePixelFormat(m_parameters.deviceContext, &pfd)))
		{
			throw System::SystemError(L"Can't choose pixel format");				
		}

		if (!SetPixelFormat(m_parameters.deviceContext, pixelFormat, &pfd))
		{
			throw System::SystemError(L"Can't set pixel format");				
		}

		HGLRC tempContext;
		if ((tempContext = wglCreateContext(m_parameters.deviceContext)) == NULL)
		{
			throw System::SystemError(L"Can't create temporary opengl context");
		}

		if (!wglMakeCurrent(m_parameters.deviceContext, tempContext))
		{
			throw System::SystemError(L"Can't set created context to be current");				
		}

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

		int forward = 0;
		int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
		};

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetProcAddress("wglCreateContextAttribsARB");

		InitExtensions(&m_parameters);
		if (!(m_parameters.openglContext = wglCreateContextAttribsARB(m_parameters.deviceContext, 0, attributes)))
		{
			throw System::SystemError(L"Can't create opengl 3.x context");				
		}

		if (!wglMakeCurrent(m_parameters.deviceContext, m_parameters.openglContext))
		{
			throw System::SystemError(L"Can't set opengl 3.x context to be current");				
		}

		wglDeleteContext(tempContext);
		InitExtensions(&m_parameters);

		GLenum err = glGetError();

		SetFocus(m_parameters.window);

		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		CheckError();
		glEnable(GL_DEPTH_TEST);

		CheckError();

		GLint t;

		System::Logger::Instance()->WriteMessage(System::string::Format(L"\tRenderer: %s ", System::string((const char*)glGetString(GL_RENDERER)).Data()));
		System::Logger::Instance()->WriteMessage(L"\tVendor: " + System::string((const char*)glGetString(GL_VENDOR)));
		System::Logger::Instance()->WriteMessage(L"\tVersion: " + System::string((const char*)glGetString(GL_VERSION)));
		System::Logger::Instance()->WriteMessage(L"\tGLSL version: " + System::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
		System::Logger::Instance()->WriteMessage(System::string::Format(L"\tMax vertex attribs: %d", t));
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
		System::Logger::Instance()->WriteMessage(System::string::Format(L"\tMax vertex uniform components: %d", t));
		glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
		System::Logger::Instance()->WriteMessage(System::string::Format(L"\tMax varying floats: %d", t));

		wglSwapIntervalEXT(0);

		const unsigned char* sv= glGetString(GL_SHADING_LANGUAGE_VERSION);
		ShaderVersion = ((int)(sv[0]-'0'))*100;
		ShaderVersion += ((int)(sv[2]-'0'))*10;
		ShaderVersion += ((int)(sv[3]-'0'));

		sv = glGetString(GL_VERSION);
		OpenGLVersion = ((int)(sv[0]-'0'))*100;
		OpenGLVersion += ((int)(sv[2]-'0'))*10;
		OpenGLVersion += ((int)(sv[3]-'0'));

		int profile;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
		if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
			System::Logger::Instance()->WriteMessage(L"\tCore profile selected");
		if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
			System::Logger::Instance()->WriteMessage(L"\tCompatible profile selected");

		GLSLProgram::Init();
		//CgProgram::Init();
		return true;
	}
}