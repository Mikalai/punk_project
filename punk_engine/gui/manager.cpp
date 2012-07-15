#include "../system/event_manager.h"
#include "manager.h"
#include "console.h"
#include "gui_default_render.h"

namespace GUI
{
	Manager::Manager()
	{
		m_focusWidget = 0;
		m_render = new DefaultGUIRender();
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Manager::OnMouseMove));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(this, &Manager::OnMouseLeftDown));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(this, &Manager::OnMouseLeftUp));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Manager::OnIdle));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(this, &Manager::OnMouseWheel));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_HOOVER, System::EventHandler(this, &Manager::OnMouseHoover));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_CHAR, System::EventHandler(this, &Manager::OnKeyChar));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Manager::OnResize));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Manager::OnKeyDownHandler));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_UP, System::EventHandler(this, &Manager::OnKeyUpHandler));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_ENTER, System::EventHandler(this, &Manager::OnMouseEnter));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LEAVE, System::EventHandler(this, &Manager::OnMouseLeave));
	}

	Manager::~Manager()
	{
		rootWidgets.clear();
	}

	void Manager::Render()
	{
		m_render->Begin(0, 0, System::Window::Instance()->GetWidth(), System::Window::Instance()->GetHeight());
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); ++it)
		{
			(*it)->Render(m_render);
		}
		m_render->End();
	}

	void Manager::SetGUIRender(IGUIRender* render)
	{
		m_render = render;
	}

	void Manager::AddRootWidget(Widget* widget)
	{
		widget->SetManager(this);
		rootWidgets.push_back(std::shared_ptr<Widget>(widget));
	}

	void Manager::OnMouseHoover(System::Event* event)
	{
	}

	void Manager::OnMouseWheel(System::Event* event)
	{
		System::MouseWheelEvent* e = static_cast<System::MouseWheelEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if (!(*it)->IsVisible() || !(*it)->IsEnabled())
				continue;
			if ((*it)->IsPointIn(Widget::WindowToViewport(e->x, e->y)))
			{
				(*it)->OnMouseWheel(e);
			}
		}
	}

	void Manager::OnMouseEnter(System::Event* event)
	{
		System::MouseEnterEvent* e = static_cast<System::MouseEnterEvent*>(event);		
		if (e->anyData)
			static_cast<Widget*>(event->anyData)->OnMouseEnter(e);
	}

	void Manager::OnMouseLeave(System::Event* event)
	{
		System::MouseLeaveEvent* e = static_cast<System::MouseLeaveEvent*>(event);		
		if (e->anyData)
			static_cast<Widget*>(event->anyData)->OnMouseLeave(e);
	}

	void Manager::SetFocusedWidget(Widget* newFocuseWidget)
	{
		if (newFocuseWidget)
		{
			System::Logger::Instance()->WriteMessage(newFocuseWidget->GetText());
			if (m_focusWidget)
			{
				System::SetUnFocusedEvent* unfocuseEvent = System::SetUnFocusedEvent::Raise();
				unfocuseEvent->anyData = m_focusWidget;
				System::EventManager::Instance()->FixEvent(unfocuseEvent);
				m_focusWidget->SetFocuse(false);					
			}

			System::SetFocusedEvent* focuseEvent = System::SetFocusedEvent::Raise();
			focuseEvent->anyData = newFocuseWidget;
			System::EventManager::Instance()->FixEvent(focuseEvent);

			newFocuseWidget->SetFocuse(true);
			m_focusWidget = newFocuseWidget;
		}
	}

	void Manager::OnMouseLeftDown(System::Event* event)
	{
		System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
		Widget* newFocuseWidget = 0;
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if (!(*it)->IsVisible() || !(*it)->IsEnabled())
				continue;

			if ((*it)->IsPointIn(Widget::WindowToViewport(e->x, e->y)))
			{
				newFocuseWidget = (*it)->GetFocused(e->x, e->y);
				(*it)->OnMouseLeftButtonDown(e);
				break;
			}
		}
		if (newFocuseWidget)
		{
			System::Logger::Instance()->WriteMessage(newFocuseWidget->GetText());
			if (m_focusWidget)
			{
				System::SetUnFocusedEvent* unfocuseEvent = System::SetUnFocusedEvent::Raise();
				unfocuseEvent->anyData = m_focusWidget;
				System::EventManager::Instance()->FixEvent(unfocuseEvent);
				m_focusWidget->SetFocuse(false);					
			}

			System::SetFocusedEvent* focuseEvent = System::SetFocusedEvent::Raise();
			focuseEvent->anyData = newFocuseWidget;
			System::EventManager::Instance()->FixEvent(focuseEvent);

			newFocuseWidget->SetFocuse(true);
			m_focusWidget = newFocuseWidget;
			m_focusWidget->OnMouseLeftButtonDown(e);					
		}
	}

	void Manager::OnMouseLeftUp(System::Event* event)
	{
		System::MouseLeftButtonUpEvent* e = static_cast<System::MouseLeftButtonUpEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if ((*it)->IsPointIn(Widget::WindowToViewport(e->x, e->y)))
			{
				Widget* w = (*it)->GetFocused(e->x, e->y);
				if (w)
					w->OnMouseLeftButtonUp(e);
			}
		}
	}

	void Manager::OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if (!(*it)->IsVisible() || !(*it)->IsEnabled())
				continue;
			bool wasIn = (*it)->IsPointIn(Widget::WindowToViewport(e->x_prev, e->y_prev));
			bool isIn = (*it)->IsPointIn(Widget::WindowToViewport(e->x, e->y));

			if (!wasIn && isIn)
			{
				System::MouseEnterEvent* new_event = System::MouseEnterEvent::Raise();
				new_event->anyData = (*it).get();
				System::EventManager::Instance()->FixEvent(new_event);
			}

			if (wasIn && !isIn)
			{
				System::MouseLeaveEvent* new_event = System::MouseLeaveEvent::Raise();
				new_event->anyData = (*it).get();
				System::EventManager::Instance()->FixEvent(new_event);
			}

			if (isIn)
			{
				(*it)->OnMouseMove(e);
			}
		}
	}

	void Manager::OnIdle(System::Event* event)
	{		
		System::IdleEvent* e = static_cast<System::IdleEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			(*it)->OnIdle(e);			
		}

	}

	void Manager::OnKeyChar(System::Event* event)
	{
		if (m_focusWidget)
			m_focusWidget->OnKeyChar(static_cast<System::KeyCharEvent*>(event));	
	}

	void Manager::OnResize(System::Event* event)
	{
		System::WindowResizeEvent* e = static_cast<System::WindowResizeEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); ++it)
		{
			(*it)->OnResize(e);			
			for (int i = 0; i < (*it)->GetChildrenCount(); ++i)
			{
				(*it)->GetChild(i)->OnResize(e);
			}
		}
	}

	void Manager::OnKeyDownHandler(System::Event* event)
	{
		System::KeyDownEvent* e = static_cast<System::KeyDownEvent*>(event);
	//	switch (e->key)
	//	{
	//	case System::PUNK_KEY_SHIFT:
	//		{
	////			System::Mouse::Instance()->Show(System::Mouse::Instance()->IsLocked());
	////			System::Mouse::Instance()->LockInWindow(!System::Mouse::Instance()->IsLocked());				
	//		}
	//		break;
	//	}
		if (m_focusWidget)
			m_focusWidget->OnKeyDown(e);
	}

	void Manager::OnKeyUpHandler(System::Event* event)
	{
	}
}

