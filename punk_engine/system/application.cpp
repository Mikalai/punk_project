#include "application.h"
#include "window.h"
#include "singletone.h"
#include "keyboard.h"
#include "mouse.h"
#include "event_manager.h"
#include "logger.h"
#include "console.h"
#include "clock.h"

namespace System
{
	SingletoneImplementation(Application);

	int Application::Run()
	{
		return Window::GetInstance()->Loop();
	}

	Window* Application::GetWindow()
	{
		return Window::GetInstance();
	}

	EventManager* Application::GetEventManager()
	{
		return EventManager::GetInstance();
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
}