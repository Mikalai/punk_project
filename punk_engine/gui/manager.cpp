#include "../system/allocator.h"
#include "../system/event_manager.h"
#include "manager.h"
#include "console.h"

namespace GUI
{
	Driver::GLSLProgram Manager::program;
	System::Window* Manager::desktop;
	Manager::Manager(System::Window* wnd)
	{
		desktop = wnd;
		//program.CreateFromFile("e:\\my projects\\punkengine\\data\\src\\shaders\\solid_color_2d.vert", "e:\\my projects\\punkengine\\data\\src\\shaders\\solid_color_2d.frag");

		//desktop->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(this, &Manager::Update));
	}

	Manager::~Manager()
	{
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
		{
			delete *it;
		}

		rootWidgets.clear();
	}

	void Manager::AddRootWidget(Widget* widget)
	{
		rootWidgets.push_back(widget);
	}

	void Manager::Update(System::Event* event)
	{
		for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
			(*it)->Render();
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
			{
				if (event->anyData)
					static_cast<Widget*>(event->anyData)->EventHandler(event);
			}
			break;
		case System::EVENT_MOUSE_LEAVE:
		case System::EVENT_MOUSE_ENTER:
			{
				if (event->anyData)
					static_cast<Widget*>(event->anyData)->EventHandler(event);
			}
			break;
		case System::EVENT_IDLE:
			{
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
					(*it)->EventHandler(event);
				Update(event);
			}
			break;
		case System::EVENT_KEY_CHAR:				
			{
				if (m_focusWidget)
					m_focusWidget->EventHandler(event);				
			}
			break;		
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
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
				{
					if (!(*it)->IsVisible() || !(*it)->IsEnabled())
						continue;

					if ((*it)->IsPointIn(e->x, e->y))
					{
						(*it)->GetFocused(e->x, e->y)->EventHandler(event);
						break;
					}
				}
			}
			break;
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
				Widget* newFocuseWidget = 0;
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
				{
					if (!(*it)->IsVisible() || !(*it)->IsEnabled())
						continue;

					if ((*it)->IsPointIn(e->x, e->y))
					{
						newFocuseWidget = (*it)->GetFocused(e->x, e->y);
						break;
					}
				}
				if (newFocuseWidget)
				{
					if (m_focusWidget)
					{
						System::SetUnFocusedEvent* unfocuseEvent = System::SetUnFocusedEvent::Raise();
						unfocuseEvent->anyData = m_focusWidget;
						CommonStaff::g_eventManager.FixEvent(unfocuseEvent);
						m_focusWidget->SetFocuse(false);					
					}

					System::SetFocusedEvent* focuseEvent = System::SetFocusedEvent::Raise();
					focuseEvent->anyData = newFocuseWidget;
					CommonStaff::g_eventManager.FixEvent(focuseEvent);
															
					newFocuseWidget->SetFocuse(true);
					m_focusWidget = newFocuseWidget;
					m_focusWidget->EventHandler(e);					
				}
			}
			break;
		case System::EVENT_MOUSE_LBUTTON_UP:
			{
				System::MouseLeftButtonUpEvent* e = static_cast<System::MouseLeftButtonUpEvent*>(event);
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
				{
					if ((*it)->IsPointIn(e->x, e->y))
					{
						Widget* w = (*it)->GetFocused(e->x, e->y);
						if (w)
							w->EventHandler(e);
					}
				}
			}
			break;
		case System::EVENT_MOUSE_MOVE:
			{
				System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
				{
					if (!(*it)->IsVisible() || !(*it)->IsEnabled())
						continue;
					bool wasIn = (*it)->IsPointIn(e->x_prev, e->y_prev);
					bool isIn = (*it)->IsPointIn(e->x, e->y);
					
					if (!wasIn && isIn)
					{
						System::MouseEnterEvent* new_event = System::MouseEnterEvent::Raise();
						new_event->anyData = *it;
						CommonStaff::g_eventManager.FixEvent(new_event);
					}

					if (wasIn && !isIn)
					{
						System::MouseLeaveEvent* new_event = System::MouseLeaveEvent::Raise();
						new_event->anyData = *it;
						CommonStaff::g_eventManager.FixEvent(new_event);
					}

					if (isIn)
					{
						(*it)->EventHandler(e);
					}
				}
			}
			break;
		case System::EVENT_WINDOW_RESIZE:
			{
				for (std::vector<Widget*>::iterator it = rootWidgets.begin(); it != rootWidgets.end(); it++)
				{
					(*it)->EventHandler(event);					
				}
			}
			break;

		}
	}				
}

