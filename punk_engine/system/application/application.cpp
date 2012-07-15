#include "application.h"
#include "../window.h"
#include "../singletone.h"
#include "../keyboard.h"
#include "../mouse.h"
#include "../event_manager.h"
#include "../logger.h"
#include "../console.h"
#include "../clock.h"
#include "../../utility/utility.h"

namespace System
{
	SingletoneImplementation(Application);

	Application::Application() : m_video_driver(0), m_time_scale_nominator(1), m_time_scale_denomiator(1)
	{
	}

	int Application::Run()
	{
		return Window::Instance()->Loop();
	}

	Window* Application::GetWindow()
	{
		return Window::Instance();
	}

	EventManager* Application::GetEventManager()
	{
		return EventManager::Instance();
	}

	OpenGL::Driver* Application::GetDriver()
	{
		if (m_video_driver)
			return m_video_driver;
		return m_video_driver = new OpenGL::Driver();
	}

	Application::~Application()
	{
		Keyboard::Release();
		Mouse::Release();
		EventManager::Release();
		Clock::Release();		
		Window::Release();
		Logger::Release();
		Console::Release();
	}

	void Application::Init()
	{				
//		m_user_interface.SetSceneGraph(&m_scene_graph);
//		m_render.SetVideoDriver(GetDriver());
		Utility::FontBuilder::Instance()->Init();
		GetEventManager()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Application::Step));
		OnInit();
	}
	
	void Application::Render()
	{
		m_video_driver->ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);		
//		Render::SceneRenderVisitor visitor(m_render);
//		m_scene_graph.Visit<Render::SceneRenderVisitor, Render::SceneRenderVisitor::Data>(visitor);
		m_video_driver->SwapBuffers();
	}

	//GUI::UserInterface* Application::GetUserInterface()
	//{
	//	return &m_user_interface;
	//}

	void Application::Step(System::Event* event)
	{		
		IdleEvent* e = static_cast<IdleEvent*>(event);
		ModelTimeStepEvent* model_time = ModelTimeStepEvent::Raise();
		model_time->elapsed_time_ms = e->elapsed_time_s*1000.0*m_time_scale_nominator/m_time_scale_denomiator;
		GetEventManager()->FixEvent(model_time);
		Render();
		OnStep(e->elapsed_time_s);
	}

	void Application::OnStep(__int64 dt)
	{
		System::Clock::Instance()->Advance(dt);
	//	System::Console::Instance()->Print(System::Clock::Instance()->ToString());
	}

	void Application::OnInit()
	{
	}

	void Application::SetTimeScale(__int64 nominator, __int64 denominator)
	{
		m_time_scale_nominator = nominator;
		m_time_scale_denomiator = denominator;
	}

}
