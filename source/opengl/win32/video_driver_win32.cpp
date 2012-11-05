/*
File: Driver.cpp
Author: Abramau Mikalaj
Description: Contains implementation, for now not the best, of initialization
and deinitialization rutines
*/

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <gl/gl3.h>
#include "../driver.h"
#include "../../system/logger.h"
#include "../../system/window.h"
#include "../extensions.h"
#include "../glsl_program.h"

namespace Driver
{
	Video* g_openGLDriver;

	int Video::ShaderVersion = 0;
	int Video::OpenGLVersion = 0;

	DriverParameters Video::m_parameters;

	Video::Video() : isLaunched(false)
	{}

	bool Video::IsLaunched() const
	{
		return isLaunched;
	}

	bool Video::Init(const DriverParameters* parameters)
	{
		System::Logger::Instance()->WriteMessage(L"Starting video engine...");
		m_parameters = *parameters;
		if (!InitOpenGL())
		{
			System::Logger::Instance()->WriteError(L"OpenGL failed to initialize", LOG_LOCATION);
			return false;
		}
		if (!InitView())
		{
			System::Logger::Instance()->WriteError(L"Unable to initialize view", LOG_LOCATION);
			return false;
		}
		isLaunched = true;
		System::Logger::Instance()->WriteMessage(L"Video driver initialized successfully...");
		return true;
	}

	bool Video::InitView()
	{
		System::Logger::Instance()->WriteMessage(L"Initialize view...");
		glViewport(0, 0, m_parameters.width, m_parameters.height);//m_parameters.width, m_parameters.height);
		System::Logger::Instance()->WriteMessage(L"View initialized...");
		return true;
	}

	bool Video::OnResize()
	{
		System::Logger::Instance()->WriteMessage(L"Video driver resizing window...");
		if (!m_parameters.fullScreen)
		{
			RECT rect;
			GetClientRect(m_parameters.window, &rect);
			m_parameters.width = rect.right - rect.left;
			m_parameters.height = rect.bottom - rect.top;
			System::Logger::Instance()->WriteMessage(System::string::Format(L"New resolution is: %dx%d", m_parameters.width, m_parameters.height));
		}
		InitView();
		System::Logger::Instance()->WriteMessage(L"Resized successfull...");
		return true;
	}

	bool Video::InitOpenGL()
	{
		System::Logger::Instance()->WriteMessage(L"Initializing OpenGL...");
		m_parameters.deviceContext = ::GetDC(m_parameters.window);

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

	bool Video::MakeFullScreen(bool full)
	{
		if (full)
			System::Logger::Instance()->WriteMessage(L"Enter full screen mode...");
		else
			System::Logger::Instance()->WriteMessage(L"Enter windowed mode...");
		m_parameters.fullScreen = full;
		if (Reboot())
		{
			System::Logger::Instance()->WriteMessage(L"Screen mode changed successfully...");
			return true;
		}
		else
		{
			System::Logger::Instance()->WriteMessage(L"Failed to change screen mode...");
			return false;
		}
	}

	bool Video::Reboot(const DriverParameters* params)
	{
		System::Logger::Instance()->WriteMessage(L"Rebooting vide driver...");
		if (params)
			m_parameters = *params;

		if (!m_parameters.fullScreen)
		{
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
			MoveWindow(m_parameters.window, 100, 100, m_parameters.width, m_parameters.height, TRUE);
		}
		else
		{
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
				return false;

			ShowCursor(FALSE);
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
		UpdateWindow(m_parameters.window);

		System::Logger::Instance()->WriteMessage(L"Ok...");
		return true;
	}

	Video::~Video()
	{
		System::Logger::Instance()->WriteMessage(L"Destroying video driver...");
		ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(m_parameters.deviceContext,NULL);
		wglDeleteContext(m_parameters.openglContext);
		ReleaseDC(m_parameters.window, m_parameters.deviceContext);
		System::Logger::Instance()->WriteMessage(L"Video driver destroyed...");
	}

	bool Video::MakeScreenShot()
	{
		System::Logger::Instance()->WriteMessage(L"Making screenshot...");
		FILE *f = 0;
		fopen_s(&f, "screenshot.bmp", "wb");
		if (f == 0)
			return false;
		try
		{
			GLubyte* data = 0;
			GLenum type = 0;
			if (m_parameters.bitsPerPixel == 8)
			{
				type = GL_UNSIGNED_BYTE_2_3_3_REV;
				data = new GLubyte[m_parameters.width*m_parameters.height];
				memset(data, 0, m_parameters.width*m_parameters.height);
			}
			else if (m_parameters.bitsPerPixel == 16)
			{
				type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
				data = new GLubyte[m_parameters.width*m_parameters.height*2];
				memset(data, 0, m_parameters.width*m_parameters.height*2);
			}
			else if (m_parameters.bitsPerPixel == 32)
			{
				type = GL_UNSIGNED_INT_8_8_8_8_REV;
				data = new GLubyte[m_parameters.width*m_parameters.height*4];
				memset(data, 0, m_parameters.width*m_parameters.height*4);
			}
			else
				return false;

			try
			{
				glReadPixels(0, 0, m_parameters.width, m_parameters.height, GL_RGBA, type, data);

				BITMAP_FILEHEADER fileHeader;
				memset(&fileHeader, 0, sizeof(fileHeader));
				fileHeader.Signature= 19778;
				fileHeader.Reserved = 0;
				fileHeader.Size = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER)+m_parameters.width*m_parameters.height*3;
				fileHeader.BitsOffset = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER);
				BITMAP_HEADER infoHeader;
				memset(&infoHeader, 0, sizeof(infoHeader));
				infoHeader.SizeImage = sizeof(infoHeader);
				infoHeader.Width = m_parameters.width;
				infoHeader.Height = m_parameters.height;
				infoHeader.Planes = 1;
				switch (type)
				{
				case GL_UNSIGNED_BYTE_2_3_3_REV:
					infoHeader.BitCount = 8;
					break;
				case GL_UNSIGNED_SHORT_4_4_4_4_REV:
					infoHeader.BitCount = 16;
					break;
				case GL_UNSIGNED_INT_8_8_8_8_REV:
					infoHeader.BitCount = 24;
					break;
				default:
					return false;
				}
				infoHeader.Compression = 0;
				fwrite(&fileHeader, sizeof(fileHeader), 1, f);
				fwrite(&infoHeader, sizeof(infoHeader), 1, f);
				if (type == GL_UNSIGNED_INT_8_8_8_8_REV)
				{
					for (unsigned i = 0; i < m_parameters.width*m_parameters.height; i++)
					{
						fwrite(data + i*4 + 2, sizeof(data[0]), 1, f);
						fwrite(data + i*4 + 1, sizeof(data[0]), 1, f);
						fwrite(data + i*4, sizeof(data[0]), 1, f);
					}
				}
				else if (type == GL_UNSIGNED_SHORT_4_4_4_4_REV)
				{
					throw System::SystemError(L"I don't know how to export 4 bits per red \
											4 bits per green 4 bits per blue and 4 bits per alpha surface \
											into bitmap with 16 bits per pixel" + LOG_LOCATION_STRING);
				}
				else if (type == GL_UNSIGNED_BYTE_2_3_3_REV)
				{
					throw System::SystemError(L"Oh, the same shit like with 16 bits" + LOG_LOCATION_STRING);
				}

				delete[] data;
			}
			catch (...)
			{
				delete[] data;
				throw;
			}
			fclose(f);
		}
		catch (...)
		{
			fclose(f);
			throw;
		}
		System::Logger::Instance()->WriteMessage(L"Done...");
		return true;
	}

	bool Video::SwapBuffers()
	{
		::SwapBuffers(m_parameters.deviceContext);				
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		return true;
	}

	bool Video::IsExtensionSupported(const char* ext)
	{			
		System::Logger::Instance()->WriteError(L"Not implemented", LOG_LOCATION);
		throw System::NotImplemented();
	}

	const DriverParameters* Video::GetParameters() const
	{
		return &m_parameters;
	}

	Video* Video::GetDriver()
	{
		if (g_openGLDriver)
			return g_openGLDriver;
		g_openGLDriver = new Video();
		return g_openGLDriver;
	}

	void Video::DestroyDriver()
	{
		if (g_openGLDriver)
		{
			delete g_openGLDriver;
			g_openGLDriver = 0;
		}
	}
}

#endif
