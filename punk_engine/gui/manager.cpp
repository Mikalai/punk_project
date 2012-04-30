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
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Manager::OnMouseMove));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(this, &Manager::OnMouseLeftDown));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(this, &Manager::OnMouseLeftUp));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Manager::OnIdle));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(this, &Manager::OnMouseWheel));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_HOOVER, System::EventHandler(this, &Manager::OnMouseHoover));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_CHAR, System::EventHandler(this, &Manager::OnKeyChar));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Manager::OnResize));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Manager::OnKeyDownHandler));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_UP, System::EventHandler(this, &Manager::OnKeyUpHandler));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_ENTER, System::EventHandler(this, &Manager::OnMouseEnter));
		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_LEAVE, System::EventHandler(this, &Manager::OnMouseLeave));
	}

	Manager::~Manager()
	{
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			delete *it;
		}

		rootWidgets.clear();
	}

	void Manager::Render()
	{
		m_render->Begin(0, 0, System::Window::GetInstance()->GetWidth(), System::Window::GetInstance()->GetHeight());
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
		rootWidgets.push_back(widget);
	}

	void Manager::OnMouseHoover(System::Event* event)
	{
	}

	void Manager::OnMouseWheel(System::Event* event)
	{
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

	void Manager::OnMouseLeftDown(System::Event* event)
	{
		System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
		Widget* newFocuseWidget = 0;
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
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
			System::Logger::GetInstance()->WriteMessage(newFocuseWidget->GetText());
			if (m_focusWidget)
			{
				System::SetUnFocusedEvent* unfocuseEvent = System::SetUnFocusedEvent::Raise();
				unfocuseEvent->anyData = m_focusWidget;
				System::EventManager::GetInstance()->FixEvent(unfocuseEvent);
				m_focusWidget->SetFocuse(false);					
			}

			System::SetFocusedEvent* focuseEvent = System::SetFocusedEvent::Raise();
			focuseEvent->anyData = newFocuseWidget;
			System::EventManager::GetInstance()->FixEvent(focuseEvent);

			newFocuseWidget->SetFocuse(true);
			m_focusWidget = newFocuseWidget;
			m_focusWidget->EventHandler(e);					
		}
	}

	void Manager::OnMouseLeftUp(System::Event* event)
	{
		System::MouseLeftButtonUpEvent* e = static_cast<System::MouseLeftButtonUpEvent*>(event);
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
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
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if (!(*it)->IsVisible() || !(*it)->IsEnabled())
				continue;
			bool wasIn = (*it)->IsPointIn(Widget::WindowToViewport(e->x_prev, e->y_prev));
			bool isIn = (*it)->IsPointIn(Widget::WindowToViewport(e->x, e->y));

			if (!wasIn && isIn)
			{
				System::MouseEnterEvent* new_event = System::MouseEnterEvent::Raise();
				new_event->anyData = *it;
				System::EventManager::GetInstance()->FixEvent(new_event);
			}

			if (wasIn && !isIn)
			{
				System::MouseLeaveEvent* new_event = System::MouseLeaveEvent::Raise();
				new_event->anyData = *it;
				System::EventManager::GetInstance()->FixEvent(new_event);
			}

			if (isIn)
			{
				(*it)->EventHandler(e);
			}
		}
	}

	void Manager::OnIdle(System::Event* event)
	{		
		System::IdleEvent* e = static_cast<System::IdleEvent*>(event);
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			(*it)->OnIdle(e);			
		}

	}

	void Manager::OnKeyChar(System::Event* event)
	{
		if (m_focusWidget)
			m_focusWidget->EventHandler(event);	
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
		switch (e->key)
		{
		case System::PUNK_KEY_SHIFT:
			{
				System::Mouse::GetInstance()->Show(System::Mouse::GetInstance()->IsLocked());
				System::Mouse::GetInstance()->LockInWindow(!System::Mouse::GetInstance()->IsLocked());				
			}
			break;
		}
	}

	void Manager::OnKeyUpHandler(System::Event* event)
	{
	}

	void Manager::SendChildren(System::Event* event)
	{
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			(*it)->EventHandler(event);
		}
	}

	void Manager::EventHandler(System::Event* event)
	{
		switch(event->eventCode)
		{
		case System::EVENT_SET_FOCUSED:
		case System::EVENT_SET_UNFOCUSED:
		case System::EVENT_MOUSE_LEAVE:
		case System::EVENT_MOUSE_ENTER:
		case System::EVENT_IDLE:
		case System::EVENT_KEY_CHAR:				
		case System::EVENT_KEY_DOWN:
			{
				//Driver::CheckError(L"Bug checking");
				if (m_focusWidget)
					m_focusWidget->EventHandler(event);
			}
			break;
		case System::EVENT_KEY_UP:
			{
				if (m_focusWidget)
					m_focusWidget->EventHandler(event);
			}
			break;
		case System::EVENT_MOUSE_WHEEL:
			//{
			//	System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
			//	for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
			//	{
			//		if (!(*it)->IsVisible() || !(*it)->IsEnabled())
			//			continue;

			//		if ((*it)->IsPointIn(e->x, e->y))
			//		{
			//			(*it)->GetFocused(e->x, e->y)->EventHandler(event);
			//			break;
			//		}
			//	}
			//}
			//break;
		case System::EVENT_WINDOW_RESIZE:
			{
			}
			break;
		}
	}				
}

