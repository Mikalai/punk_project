#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "../../gpu_config.h"
#include "../../../config.h"
#include "../../../system/smart_pointers/module.h"

#include "../../../system/module.h"
#include "../gl/module.h"
#include "../error/module.h"
#include "gl_driver.h"
#include "../../../math/vec4.h"
#include "../../common/frame.h"

namespace GPU
{
	using namespace OpenGL;

	void* GetGPUProcAddress(const char* name)
	{
		void* res = (void*)wglGetProcAddress(name);
		if (res != 0)
			return res;
		HMODULE lib = LoadLibrary(L"OpenGL32.dll");
		res = (void*)::GetProcAddress(lib, name);
		FreeLibrary(lib);
		GetLastError();
		return res;
	}


	VideoDriverImpl::VideoDriverImpl(VideoDriver* driver)
		: m_driver(driver)		
	{}

	VideoDriverImpl::~VideoDriverImpl()
	{
		try
		{
			Shutdown();
		}
		catch(...)
		{
		}
	}

    void VideoDriverImpl::SetFontBuilder(Utility::FontBuilder *value)
    {
        m_font_builder = value;
    }

    Utility::FontBuilder* VideoDriverImpl::GetFontBuilder()
    {
        return m_font_builder;
    }

	void VideoDriverImpl::SetFullScreen(bool flag)
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
            if ((code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN)) != DISP_CHANGE_SUCCESSFUL)
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

	bool VideoDriverImpl::Start(const VideoDriverDesc& desc)
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
            (BYTE)m_desc.config.bits_per_pixel,
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

//		int forward = 0;
		int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
		};

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetGPUProcAddress("wglCreateContextAttribsARB");

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

		InitExtensions(GetGPUProcAddress);

		GLint t;

		out_message() << System::string("\tRenderer: %s ", System::string((const char*)glGetString(GL_RENDERER)).Data()) << std::endl;
		out_message() << L"\tVendor: " + System::string((const char*)glGetString(GL_VENDOR)) << std::endl;
		out_message() << L"\tVersion: " + System::string((const char*)glGetString(GL_VERSION)) << std::endl;
		out_message() << L"\tGLSL version: " + System::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
		out_message() << System::string("\tMax vertex attribs: %d", t) << std::endl;
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
		out_message() << System::string("\tMax vertex uniform components: %d", t) << std::endl;
		glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
		out_message() << System::string("\tMax varying floats: %d", t) << std::endl;
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

		m_desc.event_manager->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &VideoDriverImpl::OnResize));
		m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &VideoDriverImpl::OnKeyDown));

		m_memory = new VideoMemory;

		return true;
	}

	void VideoDriverImpl::Restart()
	{
		Shutdown();
		Start(m_desc);
	}

	void VideoDriverImpl::Shutdown()
	{
		out_message() << L"Clear video memory" << std::endl;
        delete m_memory;
		out_message() << L"Destroying video driver..." << std::endl;
		ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(::GetDC(*m_desc.window), NULL);
		wglDeleteContext(m_opengl_context);
		out_message() << L"Video driver destroyed..." << std::endl;
	}

	void VideoDriverImpl::SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer)
	{
		if (color_buffer || depth_buffer)
		{
			m_rt.reset(new RenderTargetTexture(color_buffer, depth_buffer));
		}
		else
		{
			m_rt.reset(new RenderTargetBackBuffer());
		}
	}

	void VideoDriverImpl::SetClearColor(const Math::vec4& color)
	{
		glClearColor(color[0], color[1], color[2], color[3]);
	}

	void VideoDriverImpl::SetClearDepth(float value)
	{
		glClearDepth(value);
	}

	void VideoDriverImpl::Clear(bool color, bool depth, bool stencil)
	{
		GLbitfield b = 0;

		if (color)
			b |= GL_COLOR_BUFFER_BIT;
		if (depth)
			b |= GL_DEPTH_BUFFER_BIT;
		if (stencil)
			b |= GL_STENCIL_BUFFER_BIT;

		glClear(b);
		ValidateOpenGL(L"Unable to clear buffer");
	}

	void VideoDriverImpl::SwapBuffers()
	{
		if (!::SwapBuffers(::GetDC(*m_desc.window)))
			out_error() << "Swap buffer failed" << std::endl;
	}

	void VideoDriverImpl::OnResize(System::Event* e)
	{
		System::WindowResizeEvent* event = dynamic_cast<System::WindowResizeEvent*>(e);
		if (!event)
			throw OpenGLInvalidValueException(L"Can't understand event");
		glViewport(0, 0, event->width, event->height);
	}

	void VideoDriverImpl::SetViewport(float x, float y, float width, float height)
	{
		if (glViewport)
			glViewport(x, y, width, height);
	}

	void VideoDriverImpl::OnKeyDown(System::Event* e)
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

    OpenGL::VideoMemory* VideoDriverImpl::GetVideoMemory()
    {
        return m_memory;
    }

    const OpenGL::VideoMemory* VideoDriverImpl::GetVideoMemory() const
    {
        return m_memory;
    }

	System::Window* VideoDriverImpl::GetWindow() { return m_desc.window; }

	VideoDriver::VideoDriver()
		: impl(new VideoDriverImpl(this))
	{}

    const Config& VideoDriverImpl::GetConfig() const
    {
        return m_desc.config;
    }

	VideoDriver::~VideoDriver()
	{
		delete impl;
		impl = nullptr;
	}

    void VideoDriver::SetFontBuilder(Utility::FontBuilder *value)
    {
        impl->SetFontBuilder(value);
    }

    Utility::FontBuilder* VideoDriver::GetFontBuilder()
    {
        return impl->GetFontBuilder();
    }

	void VideoDriver::SetFullScreen(bool flag)
	{
		impl->SetFullScreen(flag);
	}

	bool VideoDriver::Start(const VideoDriverDesc& desc)
	{
		return impl->Start(desc);
	}

	void VideoDriver::Restart()
	{
		return impl->Restart();
	}

	void VideoDriver::Shutdown()
	{
		impl->Shutdown();
	}

	Frame* VideoDriver::BeginFrame()
	{
		Frame* frame = new Frame(this);
		return frame;
	}

	void VideoDriver::EndFrame(Frame* value)
	{
		delete value;
	}

	System::Window* VideoDriver::GetWindow()
	{
		return impl->GetWindow();
	}      

	void VideoDriver::SetViewport(float x, float y, float width, float height)
	{
		impl->SetViewport(x, y, width, height);
	}

	void VideoDriver::SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer)
	{
		impl->SetRenderTarget(color_buffer, depth_buffer);
	}

	void VideoDriver::SetClearColor(const Math::vec4& color)
	{
		impl->SetClearColor(color);
	}

	void VideoDriver::SetClearDepth(float value)
	{
		impl->SetClearDepth(value);
	}

	void VideoDriver::Clear(bool color, bool depth, bool stencil)
	{
		impl->Clear(color, depth, stencil);
	}

	void VideoDriver::SwapBuffers()
	{
		impl->SwapBuffers();
	}

    const Config& VideoDriver::GetConfig() const
    {
        return impl->GetConfig();
    }
}

#endif	//	_WIN32
