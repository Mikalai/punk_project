/*
	ile: manager.h
	uthor: Mikalai Abramau
	esc: gui manager
*/

#ifndef _H_PUNK_GUI_MANAGER
#define _H_PUNK_GUI_MANAGER

#include <vector>
#include "../config.h"
#include "widget.h"
#include "gui_adapter.h"

namespace System
{
	class Window;
	class EventManager;
	class Event;
}

namespace GUI
{
	class IGUIRender;

	struct ManagerDesc
	{
		System::Window* window;
		System::EventManager* event_manager;
		Adapter* adapter;
	};

	class PUNK_ENGINE_PUBLIC Manager
	{
	public:
		void Render();

		void SetFocusedWidget(Widget* widget);
		Widget* GetFocusedWidget() { return m_focusWidget; }
		const Widget* GetFocusedWidget() const { return m_focusWidget; }
		void SetGUIRender(IGUIRender* render);
		void AddRootWidget(Widget* widget);
		void RemoveRootWidget(Widget* widget);
		void OnMouseMove(System::Event* event);
		void OnMouseLeftDown(System::Event* event);
		void OnMouseLeftUp(System::Event* event);
		void OnIdle(System::Event* event);
		void OnMouseWheel(System::Event* event);
		void OnMouseHoover(System::Event* event);
		void OnKeyChar(System::Event* event);
		void OnResize(System::Event* event);
		void OnKeyDownHandler(System::Event* event);
		void OnKeyUpHandler(System::Event* event);
		void OnMouseEnter(System::Event* event);
		void OnMouseLeave(System::Event* event);

		static void Create(const ManagerDesc& desc);
		static Manager* Instance();
		static void Destroy();
		~Manager();

		Adapter* GetAdapter() { return m_adapter; }
		System::Window* GetWindow() { return m_window; }
	
	private:
		static std::unique_ptr<Manager> m_instance;
		
		//	next pointers should be destroyed in destructor
		std::vector<Widget*> rootWidgets;

		//	next pointers should not be destroyed
		Widget* m_focusWidget;
		IGUIRender* m_render;
		System::Window* m_window;
		System::EventManager* m_event_manager;
		Adapter* m_adapter;

	private:
		Manager(const ManagerDesc& desc);		
	};
}

#endif