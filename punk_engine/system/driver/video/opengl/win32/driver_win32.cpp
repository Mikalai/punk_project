
#include "../../../../system.h"
#include "../../../../../images/images.h"
#include "driver_win32.h"
#include "extensions_win32.h"
#include "../glsl_program.h"
#include "../vertex_array_object.h"
#include "../texture2d.h"
#include "../text_texture_2d.h"

namespace OpenGL
{
	Driver::Driver()
	{
	}

	void Driver::ReadConfig()
	{
		System::ConfigFile conf;
		conf.Open(m_window->GetTitle());

		try
		{
			m_width = conf.ReadOptionInt(L"screen_width");
		}
		catch (System::FileNotFound&)
		{
			m_width = m_window->GetDesktopWidth();
			conf.WriteOptionInt(L"screen_width", m_width);
		}

		try
		{
			m_height = conf.ReadOptionInt(L"screen_height");
		}
		catch (System::FileNotFound&)
		{
			m_height = m_window->GetDesktopHeight();
			conf.WriteOptionInt(L"screen_height", m_height);
		}

		try
		{
			m_bits_per_pixel = conf.ReadOptionInt(L"bpp");
		}
		catch (System::FileNotFound&)
		{
			m_bits_per_pixel = m_window->GetDesktopBitsPerPixel();
			conf.WriteOptionInt(L"bpp", m_bits_per_pixel);
		}

		try
		{
			m_fullscreen = conf.ReadOptionInt(L"fullscreen") == 1;
		}
		catch (System::FileNotFound&)
		{
			m_fullscreen = false;
			conf.WriteOptionInt(L"fullscreen", (int)m_fullscreen);
		}

		try
		{
			m_refresh_rate = conf.ReadOptionInt(L"refresh_rate");
		}
		catch (System::FileNotFound&)
		{
			m_refresh_rate = m_window->GetDesktopRefreshRate();
			conf.WriteOptionInt(L"refresh_rate", m_refresh_rate);
		}

		try
		{
			m_path_to_textures = conf.ReadOptionString(L"textures");
		}
		catch (System::FileNotFound&)
		{
			m_refresh_rate = m_window->GetDesktopRefreshRate();
			conf.WriteOptionString(L"textures", L"D:\\project\\data\\textures\\");
		}

		conf.Close();
	}

	void Driver::Start(System::Window* wnd)
	{
		using namespace System;
		if (wnd == 0)
			throw System::SystemError(L"Invalid window to initialize driver");
		m_window = wnd;

		ReadConfig();

		System::Logger::Instance()->WriteMessage(L"Initializing OpenGL...");

		HDC deviceContext = ::GetDC(*m_window);

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
			throw System::SystemError(L"Can't choose pixel format");				
		}

		if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
		{
			throw System::SystemError(L"Can't set pixel format");				
		}

		HGLRC tempContext;
		if ((tempContext = wglCreateContext(deviceContext)) == NULL)
		{
			throw System::SystemError(L"Can't create temporary opengl context");
		}

		if (!wglMakeCurrent(deviceContext, tempContext))
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

		if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
		{
			throw System::SystemError(L"Can't create opengl 3.x context");				
		}

		if (!wglMakeCurrent(deviceContext, m_opengl_context))
		{
			throw System::SystemError(L"Can't set opengl 3.x context to be current");				
		}

		wglDeleteContext(tempContext);
		
		InitExtensions(this);

		//GLenum err = glGetError();

		//SetFocus(m_parameters.window);

	//	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	//	CheckError();
	//	glEnable(GL_DEPTH_TEST);

	//	CheckError();

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
			System::Logger::Instance()->WriteMessage(L"\tCore profile selected");
		if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
			System::Logger::Instance()->WriteMessage(L"\tCompatible profile selected");

		try
		{
		InitShaderPrograms();
		}
		catch(...)
		{
		}
		SubscribeForSystemMessages();

		InitInternalVertexBuffers();

		glClearColor(0.8, 0.8, 0.8, 1);
	//	GLSLProgram::Init();
		//CgProgram::Init();
	}

	void Driver::Shutdown()
	{
		System::Logger::Instance()->WriteMessage(L"Destroying video driver...");
		ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(::GetDC(*m_window), NULL);
		wglDeleteContext(m_opengl_context);
		System::Logger::Instance()->WriteMessage(L"Video driver destroyed...");
	}

	void Driver::SwapBuffers()
	{
		::SwapBuffers(::GetDC(*m_window));
	}

	RenderContext* Driver::GetRenderContext()
	{
		return &m_render_context;
	}

	TextureContext* Driver::GetTextureContext()
	{
		return &m_texture_context;
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

	System::Window* Driver::GetWindow()
	{
		return m_window;
	}

	void Driver::Restart()
	{
		Shutdown();
		Start(m_window);
	}

	void Driver::ClearBuffer(int mask)
	{
		GLbitfield b = 0;
		if (mask & COLOR_BUFFER)
			b |= GL_COLOR_BUFFER_BIT;
		if (mask & DEPTH_BUFFER)
			b |= GL_DEPTH_BUFFER_BIT;
		if (mask & STENCIL_BUFFER)
			b |= GL_STENCIL_BUFFER_BIT;

		glClear(b);
		CHECK_GL_ERROR(L"Unable to clear buffer");		
	}

	void Driver::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	::ShaderProgram* Driver::GetShaderProgram(const System::string& name)
	{
		std::map<System::string, GLSLProgram*>::iterator i =  m_programs.find(name);
		if (i == m_programs.end())
			return 0;
		return (*i).second;
	}
	
/*	Texture2D* Driver::GetTexture2D(const System::string& name)
	{
		std::map<System::string, Texture2D*>::iterator i = m_textures.find(name);
		if (i == m_textures.end())
		{
			ImageModule::PngFile png;
			try
			{
				png.Load((m_path_to_textures + name).Data());
			}
			catch(...)
			{
				return 0;
			}

			Texture2D* t = new Texture2D;
			t->Create(png);
			m_textures[name] = t;
			return t;
		}
		return (*i).second;
	}*/

	System::Descriptor Driver::CreateStringTexture(const System::string& init_value, int width, int height, int size, const System::string& font_name)
	{
	/*	System::Descriptor desc = System::ResourceManager::Instance()->ManageResource<System::RESOURCE_TEXT_TEXTURE>(new System::Resource<TextTexture2D>());
		auto res = System::ResourceManager::Instance()->GetResource<TextTexture2D>(desc);
		auto v = res->Lock();

		if (v->GetWidth() != width || v->GetHeight() != height)
			v->Resize(width, height);

		v->RenderText(init_value, size, font_name);

		res->Unlock();*/
		throw System::SystemError(L"Not implemented");
		//return // desc;
	}

	void Driver::AlterateStringTexture(System::Descriptor desc, const System::string& init_value, int width, int height, int size, const System::string& font_name)
	{
/*		auto res = System::ResourceManager::Instance()->GetResource<TextTexture2D>(desc);
		auto v = res->Lock();

		if (v->GetWidth() != width || v->GetHeight() != height)
			v->Resize(width, height);

		v->RenderText(init_value, size, font_name);

		res->Unlock();*/
		throw System::SystemError(L"Not implemented");
	}
			
	void Driver::Render(VertexArrayObject *object)
	{
		object->Render();
	}

	void Driver::InitShaderPrograms()
	{
		System::ConfigFile conf;
		conf.Open(System::Window::Instance()->GetTitle());
		System::string path = conf.ReadOptionString(L"shaders");
		conf.Close();

		System::Buffer buffer;
		System::BinaryFile::Load(path + L"shaders.ini", buffer);

		while (!buffer.IsEnd())
		{
			unsigned code = buffer.ReadWord().ToInt32();
			System::string name = buffer.ReadWord();
			System::string vertex = buffer.ReadWord();
			System::string fragment = buffer.ReadWord();	
			System::string geometry = buffer.ReadWord();

			GLSLProgram* p = new GLSLProgram;
			
			try
			{
				p->CreateFromFile(path+vertex, path+fragment, geometry == L"null" ? L"null" : path+geometry);
			}
			catch(...)
			{
				System::Logger::Instance()->WriteError(System::string::Format(L"Unable to make GLSL program %s", name.Data()), LOG_LOCATION);
				delete p;
				continue;
			}

			m_programs[name] = p;
		}
	}

	void Driver::OnResize(System::Event* e)
	{
		System::WindowResizeEvent* event = dynamic_cast<System::WindowResizeEvent*>(e);
		if (!event)
			throw System::SystemError(L"Can't understand event");
		glViewport(0, 0, event->width, event->height);
	}

	void Driver::SetViewport(float x, float y, float width, float height)
	{
		glViewport(x, y, width, height);
	}
	
	void Driver::SetFullScreen(bool flag)
	{
		m_fullscreen = flag;
		if (m_fullscreen)
		{
			SetWindowLong(*m_window, GWL_STYLE, WS_POPUP);
			SetWindowLong(*m_window, GWL_EXSTYLE, WS_EX_APPWINDOW);

			System::Logger::Instance()->WriteMessage(L"Fullscreen mode...");
			DEVMODE mode;
			ZeroMemory(&mode, sizeof(mode));
			mode.dmSize = sizeof(mode);
			mode.dmPelsWidth = m_width;
			mode.dmPelsHeight = m_height;
			mode.dmBitsPerPel = m_bits_per_pixel;
			mode.dmDisplayFrequency = m_refresh_rate;
			mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

			SetWindowPos(*m_window, 0, 0, 0, m_width, m_height, SWP_SHOWWINDOW);

			LONG code;
			if (code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				throw System::SystemError(L"Can't change display settings " + LOG_LOCATION_STRING);					
			}
		}
		else
		{
			SetWindowLong(*m_window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowLong(*m_window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
			
			System::Logger::Instance()->WriteMessage(L"Window mode...");
			m_window->SetPosition(30, 30);
			m_window->SetSize(2*m_width/3, 2*m_height/3);
		}

		ShowWindow(*m_window, SW_SHOW);
		SetFocus(*m_window);
	}

	void Driver::OnKeyPress(System::Event* e)
	{
		System::KeyDownEvent* event = dynamic_cast<System::KeyDownEvent*>(e);
		if (!event)
			throw System::SystemError(L"Unexpected event recieved");
		
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
			throw System::SystemError(L"Unable to get event manager");

		mgr->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Driver::OnResize));
		mgr->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Driver::OnKeyPress));
	}

	void Driver::RenderQuad()
	{
/*		System::Resource<VertexArrayObject>* vao_res = System::ResourceManager::Instance()->GetResource<VertexArrayObject>(m_quad_desc);
		VertexArrayObject* vao = vao_res->Lock();

		vao->Render();

		vao_res->Unlock();
		//m_quad->Render();*/
		throw System::SystemError(L"Not implemented");
	}

	void Driver::RenderString(const System::string& text)
	{
	}

	void Driver::Render(System::Descriptor desc)
	{
		throw System::NotImplemented();
	/*	if (desc.Type() != System::RESOURCE_VAO)
			return;

		System::Resource<VertexArrayObject>* vao_res = System::ResourceManager::Instance()->GetResource<VertexArrayObject>(desc);
		VertexArrayObject* vao = vao_res->Lock();

		vao->Render();

		vao_res->Unlock();*/
	}

	void Driver::InitInternalVertexBuffers()
	{
	/*	System::ResourceManager::Instance()->DestroyResource(m_quad_desc);
		System::ResourceManager::Instance()->DestroyResource(m_point_desc);
		m_quad_desc = System::ResourceManager::Instance()->ManageResource<System::RESOURCE_VAO>(new System::Resource<VertexArrayObject>());
		auto vao_res = System::ResourceManager::Instance()->GetResource<VertexArrayObject>(m_quad_desc);

		auto vao = vao_res->Lock();

		vao->CreateQuad();

		vao_res->Unlock();		
//		m_point_desc = System::ResourceManager::Instance()->ManageResource<System::RESOURCE_VAO>(new System::Resource<VertexArrayObject>());*/
	}
}

