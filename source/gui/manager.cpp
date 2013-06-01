#include "../system/event_manager.h"
#include "../system/window/module.h"
#include <stdexcept>
#include <memory>
#include "events/module.h"
#include "manager.h"
#include "gui_render.h"
//#include "console.h"
//#include "gui_default_render.h"

namespace GUI
{
	std::unique_ptr<Manager> Manager::m_instance;

	Manager* Manager::Instance()
	{
		if (!m_instance.get())
			throw std::logic_error("GUI manager was not created");
		return m_instance.get();
	}

	void Manager::Destroy()
	{
		m_instance.reset(nullptr);
	}

	void Manager::Create(const ManagerDesc& desc)
	{
		m_instance.reset(new Manager(desc));
	}

	Manager::Manager(const ManagerDesc& desc)
	{
		m_window = desc.window;
		m_event_manager = desc.event_manager;
		m_adapter = desc.adapter;

		m_focusWidget = 0;
		//m_render = new DefaultGUIRender();
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Manager::OnMouseMove));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(this, &Manager::OnMouseLeftDown));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(this, &Manager::OnMouseLeftUp));
		m_event_manager->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Manager::OnIdle));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(this, &Manager::OnMouseWheel));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_HOOVER, System::EventHandler(this, &Manager::OnMouseHoover));
		m_event_manager->SubscribeHandler(System::EVENT_KEY_CHAR, System::EventHandler(this, &Manager::OnKeyChar));
		m_event_manager->SubscribeHandler(System::EVENT_WINDOW_RESIZE, System::EventHandler(this, &Manager::OnResize));
		m_event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Manager::OnKeyDownHandler));
		m_event_manager->SubscribeHandler(System::EVENT_KEY_UP, System::EventHandler(this, &Manager::OnKeyUpHandler));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_ENTER, System::EventHandler(this, &Manager::OnMouseEnter));
		m_event_manager->SubscribeHandler(System::EVENT_MOUSE_LEAVE, System::EventHandler(this, &Manager::OnMouseLeave));
	}

	Manager::~Manager()
	{
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); ++it)
			safe_delete(*it);

		rootWidgets.clear();
	}

	void Manager::Render()
	{
		m_render->Begin(0, 0, m_window->GetWidth(), m_window->GetHeight());
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
		rootWidgets.push_back(widget);
	}

    void Manager::OnMouseHoover(System::Event*)
	{
	}

	void Manager::OnMouseWheel(System::Event* event)
	{
		System::MouseWheelEvent* e = static_cast<System::MouseWheelEvent*>(event);
		for (auto it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			if (!(*it)->IsVisible() || !(*it)->IsEnabled())
				continue;
			if ((*it)->IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y))))
			{
				(*it)->OnMouseWheel(e);
			}
		}
	}

	void Manager::OnMouseEnter(System::Event* event)
	{
		MouseEnterEvent* e = static_cast<MouseEnterEvent*>(event);
		if (e->anyData)
			static_cast<Widget*>(event->anyData)->OnMouseEnter(e);
	}

	void Manager::OnMouseLeave(System::Event* event)
	{
		MouseLeaveEvent* e = static_cast<MouseLeaveEvent*>(event);
		if (e->anyData)
			static_cast<Widget*>(event->anyData)->OnMouseLeave(e);
	}

	void Manager::SetFocusedWidget(Widget* newFocuseWidget)
	{
		if (newFocuseWidget)
		{
			out_message() << newFocuseWidget->GetText() << std::endl;
			if (m_focusWidget)
			{
				GUI::SetUnFocusedEvent* unfocuseEvent = new GUI::SetUnFocusedEvent;
				unfocuseEvent->anyData = m_focusWidget;
				m_adapter->OnSetUnFocusedEvent(unfocuseEvent);
				m_focusWidget->SetFocuse(false);
			}

			GUI::SetFocusedEvent* focuseEvent = new GUI::SetFocusedEvent;
			focuseEvent->anyData = newFocuseWidget;
			m_adapter->OnSetFocusedEvent(focuseEvent);

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

			if ((*it)->IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y))))
			{
				newFocuseWidget = (*it)->GetFocused(float(e->x), float(e->y));
				(*it)->OnMouseLeftButtonDown(e);
				break;
			}
		}
		if (newFocuseWidget)
		{
			out_message() << newFocuseWidget->GetText() << std::endl;
			if (m_focusWidget)
			{
				GUI::SetUnFocusedEvent* unfocuseEvent = new GUI::SetUnFocusedEvent;
				unfocuseEvent->anyData = m_focusWidget;
				m_adapter->OnSetUnFocusedEvent(unfocuseEvent);
				m_focusWidget->SetFocuse(false);
			}

			SetFocusedEvent* focuseEvent = new SetFocusedEvent;
			focuseEvent->anyData = newFocuseWidget;
			m_adapter->OnSetFocusedEvent(focuseEvent);

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
			if ((*it)->IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y))))
			{
				Widget* w = (*it)->GetFocused(float(e->x), float(e->y));
				if (w)
					w->OnMouseLeftButtonUp(e);
			}
		}
	}

	void Manager::OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
		for (auto root : rootWidgets)
		{
			if (!root)
				continue;

			if (!root->IsVisible() || !root->IsEnabled())
				continue;
			bool wasIn = root->IsPointIn(Widget::WindowToViewport(float(e->x_prev), float(e->y_prev)));
			bool isIn = root->IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y)));

			if (!wasIn && isIn)
			{
				MouseEnterEvent* new_event = new MouseEnterEvent;
				new_event->anyData = root;
				m_adapter->OnMouseEnterEvent(new_event);
			}

			if (wasIn && !isIn)
			{
				MouseLeaveEvent* new_event = new MouseLeaveEvent;
				new_event->anyData = root;
				m_adapter->OnMouseLeaveEvent(new_event);
			}

			if (isIn)
			{
				root->OnMouseMove(e);
			}
		}
	}

	void Manager::OnIdle(System::Event* event)
	{
		System::IdleEvent* e = static_cast<System::IdleEvent*>(event);
		for (auto root : rootWidgets)
		{
			if (!root)
				continue;
			root->OnIdle(e);
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
		for (auto root : rootWidgets)
		{
			if (!root)
				continue;
			root->OnResize(e);
			//for each(System::Proxy<Widget> child in *root)
			//{
			//	child->OnResize(e);
			//}
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

    void Manager::OnKeyUpHandler(System::Event*)
	{
	}
}

