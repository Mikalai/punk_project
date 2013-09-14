#include "application.h"
#include "../system/module.h"
#include "../gpu/module.h"
#include "../utility/module.h"
#include "../gui/module.h"
#include "../physics/module.h"
#include "../virtual/module.h"
#include "../gpu/opengl/module.h"

namespace Punk
{

	Application::Application()
		: m_time_scale_nominator(1)
		, m_time_scale_denomiator(1)
		, m_video_driver(nullptr)
        , m_async_parser(new Utility::AsyncParser)
	{
		m_paint_engine = nullptr;
	}

	Application::~Application()
	{		        
	}

	void Application::Clear()
    {
        safe_delete(m_async_parser);
        OnDestroy();
		safe_delete(m_font_builder);        
        Virtual::StaticGeometry::Info.DestroyAllInstances();
        Virtual::SkinGeometry::Info.DestroyAllInstances();
        Virtual::Armature::Info.DestroyAllInstances();
        Virtual::Material::Info.DestroyAllInstances();
		safe_delete(m_paint_engine);
//		GUI::Manager::Destroy();
		safe_delete(m_terrain_manager);
		safe_delete(m_simulator);
        Gpu::Destroy(m_video_driver);
		safe_delete(m_window);
		safe_delete(m_event_manager);
    }


    void Application::Init(const Config& data)
    {
        m_font_builder = new Utility::FontBuilder;

        m_event_manager = new System::EventManager();
        System::WindowDesc wnd_desc;
        wnd_desc.m_width = data.gpu_config.view_width;
        wnd_desc.m_height = data.gpu_config.view_height;
        m_window = new System::Window(this, wnd_desc);
        if (!data.gpu_config.disable_3d_graphics)
        {
            System::Mouse::Instance()->LockInWindow(true);
            {
                Gpu::VideoDriverDesc desc;
                desc.config = data.gpu_config;
                desc.event_manager = m_event_manager;
                desc.window = m_window;
                desc.font_builder = m_font_builder;
                m_video_driver = Gpu::Init(desc);
            }

            //		{
            //			GUI::ManagerDesc man_desc;
            //			man_desc.adapter = this;
            //			man_desc.event_manager = m_event_manager;
            //			man_desc.window = m_window;
            //			GUI::Manager::Create(man_desc);
            //		}

            {
                m_simulator =  nullptr;
                //	m_simulator = new Physics::Simulator;
                //	m_simulator->Init();
            }

            {
                Virtual::TerrainManagerDesc desc;
                desc.memory_usage = 1024*1024*1024;
                desc.threshold = 32.0f;
                desc.view_size = 1024;
                desc.simulator = m_simulator;
                m_terrain_manager = new Virtual::TerrainManager(desc);
            }

            {
                //			m_paint_engine = new Gpu::OpenGL::OpenGLPaintEngine;
                //			m_paint_engine->SetSurfaceSize(GetWindow()->GetWidth(), GetWindow()->GetHeight());
            }
        }
		OnInit(data);
	}

	void Application::WndOnIdleEvent(System::IdleEvent* event)
	{
        Idle(event);
		//m_simulator->Update(float(event->elapsed_time_s));
		m_event_manager->FixEvent(event);
		m_event_manager->Process();

        if (GetVideoDriver())
            Render();
	}

	void Application::WndOnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event)
	{        
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event)
	{
        MouseRightButtonDown(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event)
	{
        MouseLeftButtonDown(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseHooverEvent(System::MouseHooverEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseMoveEvent(System::MouseMoveEvent* event)
	{
		MouseMove(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnMouseWheelEvent(System::MouseWheelEvent* event)
	{
		MouseWheel(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnCharEvent(System::KeyCharEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnWideCharEvent(System::KeyWCharEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnKeyDownEvent(System::KeyDownEvent* event)
	{
		KeyDown(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnKeyUpEvent(System::KeyUpEvent* event)
	{
		KeyUp(event);
		m_event_manager->FixEvent(event);
	}

	void Application::WndOnResizeEvent(System::WindowResizeEvent* event)
	{
		Resize(event);
	}

	void Application::WndOnCreateEvent()
	{
	}

	void Application::WndOnDestroyEvent()
	{
		Clear();
	}

	void Application::OnSetFocusedEvent(GUI::SetFocusedEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnSetUnFocusedEvent(GUI::SetUnFocusedEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseEnterEvent(GUI::MouseEnterEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseLeaveEvent(GUI::MouseLeaveEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	int Application::Run()
	{
		return m_window->Loop();
	}

	System::Window* Application::GetWindow()
	{
		return m_window;
	}

	System::EventManager* Application::GetEventManager()
	{
		return m_event_manager;
	}

	Gpu::VideoDriver* Application::GetVideoDriver()
	{
		return m_video_driver;
	}

    Utility::AsyncParser* Application::GetAsyncParser()
    {
        return m_async_parser;
    }

	GUI::Manager* Application::GetGUIManager()
	{
		return GUI::Manager::Instance();
	}

	Virtual::TerrainManager* Application::GetTerrainManager()
	{
		return m_terrain_manager;
	}

	void Application::SetTimeScale(int64_t nominator, int64_t denominator)
	{
		m_time_scale_nominator = nominator;
		m_time_scale_denomiator = denominator;
	}

	Physics::Simulator* Application::GetSimulator()
	{
		return m_simulator;
	}

	Gpu::PaintEngine* Application::GetPaintEngine()
	{
		return m_paint_engine;
	}

    void Application::OnRender(Gpu::Frame*)
    {

    }

	void Application::OnInit(const Config &value)
	{

	}

    void Application::Render()
    {
        Gpu::VideoDriver* driver = GetVideoDriver();
        if (!driver)
            return;

        Gpu::Frame* frame = driver->BeginFrame();
        if (!frame)
            return;

        OnRender(frame);
        driver->EndFrame(frame);
    }

#ifdef _WIN32
    LRESULT Application::CustomDefWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        return GetWindow()->CustomDefWindowProc(wnd, msg, wParam, lParam);
    }
#endif

	void Application::OnResize(System::WindowResizeEvent *event)
	{}

	void Application::OnKeyDown(System::KeyDownEvent *event)
	{}

	void Application::OnKeyUp(System::KeyUpEvent *event)
	{}

	void Application::OnMouseWheel(System::MouseWheelEvent *event)
	{}

	void Application::OnMouseMove(System::MouseMoveEvent *event)
	{}

    void Application::OnDestroy()
    {}

    void Application::OnIdle(System::IdleEvent *event)
    {}

    void Application::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent *event)
    {}

    void Application::OnMouseRightButtonDown(System::MouseRightButtonDownEvent *event)
    {}

	void Application::Resize(System::WindowResizeEvent *event)
	{
		m_event_manager->FixEvent(event);

		auto p = GetPaintEngine();
		if (p)
			p->SetSurfaceSize(event->width, event->height);

		auto driver = GetVideoDriver();
		if (driver)
		{
			driver->SetViewport(0, 0, event->width, event->height);
			OnResize(event);
		}		
	}

	void Application::KeyDown(System::KeyDownEvent *event)
	{
		OnKeyDown(event);
	}

	void Application::KeyUp(System::KeyUpEvent *event)
	{
		OnKeyUp(event);
	}

	void Application::MouseWheel(System::MouseWheelEvent *event)
	{
		OnMouseWheel(event);
	}

	void Application::MouseMove(System::MouseMoveEvent *event)
	{
		OnMouseMove(event);
	}

    void Application::MouseLeftButtonDown(System::MouseLeftButtonDownEvent* event)
    {
        OnMouseLeftButtonDown(event);
    }

    void Application::Idle(System::IdleEvent *event)
    {
        OnIdle(event);
    }

    void Application::MouseRightButtonDown(System::MouseRightButtonDownEvent *event)
    {
        OnMouseRightButtonDown(event);
    }
}
