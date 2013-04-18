#include "application.h"
#include "../system/module.h"
#include "../gpu/module.h"
#include "../utility/module.h"
#include "../gui/module.h"
#include "../physics/module.h"

namespace Punk
{

	Application::Application() : m_time_scale_nominator(1), m_time_scale_denomiator(1)
	{
		m_paint_engine = nullptr;
	}

	Application::~Application()
	{
		Virtual::StaticGeometry::clear();
		Virtual::SkinGeometry::clear();
		Virtual::Armature::clear();
		Virtual::Material::clear();
		safe_delete(m_paint_engine);
		GUI::Manager::Destroy();
		safe_delete(m_terrain_manager);
		safe_delete(m_simulator);
		GPU::GPU_DESTROY();
		safe_delete(m_video_driver);
		safe_delete(m_window);
		safe_delete(m_event_manager);
	}

	void Application::Init(const Config& data)
	{
		m_event_manager = new System::EventManager();
		m_window = new System::Window(this);
		System::Mouse::Instance()->LockInWindow(true);
		m_video_driver = new GPU::VideoDriver;

		{
			GPU::VideoDriverDesc desc;
			desc.config = data.gpu_config;
			desc.event_manager = m_event_manager;
			desc.window = m_window;
			m_video_driver->Start(desc);
		}

		{
			GPU::GPU_INIT(data.gpu_config);
		}

		{
			GUI::ManagerDesc man_desc;
			man_desc.adapter = this;
			man_desc.event_manager = m_event_manager;
			man_desc.window = m_window;
			GUI::Manager::Create(man_desc);
		}

		{
			m_simulator = new Physics::Simulator;
			m_simulator->Init();
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
			m_paint_engine = new GPU::OpenGL::OpenGLPaintEngine;
			m_paint_engine->SetSurfaceSize(GetWindow()->GetWidth(), GetWindow()->GetHeight());
		}
	}

	void Application::OnIdleEvent(System::IdleEvent* event)
	{
		m_simulator->Update(float(event->elapsed_time_s));
		m_event_manager->FixEvent(event);
		m_event_manager->Process();
	}

	void Application::OnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseHooverEvent(System::MouseHooverEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseMoveEvent(System::MouseMoveEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnMouseWheelEvent(System::MouseWheelEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnCharEvent(System::KeyCharEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnWideCharEvent(System::KeyWCharEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnKeyDownEvent(System::KeyDownEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnKeyUpEvent(System::KeyUpEvent* event)
	{
		m_event_manager->FixEvent(event);
	}

	void Application::OnResizeEvent(System::WindowResizeEvent* event)
	{
		m_event_manager->FixEvent(event);

		auto p = GetPaintEngine();
		if (p)
			p->SetSurfaceSize(event->width, event->height);


	}

	void Application::OnCreateEvent()
	{
	}

	void Application::OnDestroyEvent()
	{
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

	GPU::VideoDriver* Application::GetVideoDriver()
	{
		return m_video_driver;
	}

	GUI::Manager* Application::GetGUIManager()
	{
		return GUI::Manager::Instance();
	}

	Virtual::TerrainManager* Application::GetTerrainManager()
	{
		return m_terrain_manager;
	}

	void Application::SetTimeScale(__int64 nominator, __int64 denominator)
	{
		m_time_scale_nominator = nominator;
		m_time_scale_denomiator = denominator;
	}

	Physics::Simulator* Application::GetSimulator()
	{
		return m_simulator;
	}

	GPU::PaintEngine* Application::GetPaintEngine()
	{
		return m_paint_engine;
	}
}
