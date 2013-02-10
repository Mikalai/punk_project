#include "application.h"
#include "../system/module.h"
#include "../gpu/module.h"
#include "../utility/module.h"
#include "../gui/module.h"

namespace Punk
{

	Application::Application() : m_time_scale_nominator(1), m_time_scale_denomiator(1)
	{
	}

	Application::~Application()
	{
		Virtual::StaticGeometry::clear();
		Virtual::SkinGeometry::clear();
		Virtual::Armature::clear();
		Virtual::Material::clear();
		GUI::Manager::Destroy();
		Utility::FontBuilder::Destroy();
		GPU::GPU_DESTROY();
		m_video_driver.Release();
		m_window.Release();		
		m_event_manager.Release();
	}
	void Application::Init(const Config& data)
	{	
		m_event_manager.Reset(new System::EventManager());
		m_window.Reset(new System::Window(this));
		System::Mouse::Instance()->LockInWindow(true);
		m_video_driver.Reset(new GPU::OpenGL::Driver);
		GPU::OpenGL::DriverDesc desc;
		desc.config = data.gpu_config;
		desc.event_manager = m_event_manager;
		desc.window = m_window;
		m_video_driver->Start(desc);

		GPU::GPU_INIT(data.gpu_config);
		Utility::FontBuilder::Instance()->Init();	

		GUI::ManagerDesc man_desc;
		man_desc.adapter = this;
		man_desc.event_manager = m_event_manager;
		man_desc.window = m_window;
		GUI::Manager::Create(man_desc);
	}

	void Application::OnIdleEvent(System::IdleEvent* event)
	{
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

	System::Proxy<System::Window> Application::GetWindow()
	{
		return m_window;
	}

	System::Proxy<System::EventManager> Application::GetEventManager()
	{
		return m_event_manager;
	}

	System::Proxy<GPU::OpenGL::Driver> Application::GetDriver()
	{
		return m_video_driver;
	}

	GUI::Manager* Application::GetGUIManager()
	{
		return GUI::Manager::Instance();
	}

	void Application::SetTimeScale(__int64 nominator, __int64 denominator)
	{
		m_time_scale_nominator = nominator;
		m_time_scale_denomiator = denominator;
	}

}
