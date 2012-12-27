/*
	ile: manager.h
	uthor: Mikalai Abramau
	esc: gui manager
*/

#ifndef _H_PUNK_GUI_MANAGER
#define _H_PUNK_GUI_MANAGER

#include "../config.h"
#include "widget.h"
#include "../system/events/events.h"
#include "../system/window.h"

#include <vector>

namespace GUI
{
	class IGUIRender;

	class PUNK_ENGINE Manager
	{
	public:
		void Render();

		void SetFocusedWidget(Widget* widget);
		Widget* GetFocusedWidget() { return m_focusWidget; }
		const Widget* GetFocusedWidget() const { return m_focusWidget; }
		void SetGUIRender(IGUIRender* render);
		void AddRootWidget(System::Proxy<Widget> widget);
		void RemoveRootWidget(System::Proxy<Widget> widget);
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

		static Manager* Instance();
		static void Destroy();
		~Manager();

	private:
		static std::auto_ptr<Manager> m_instance;
		std::vector<System::Proxy<Widget>> rootWidgets;
		Widget* m_focusWidget;
		IGUIRender* m_render;

		Manager();		
	};
}

#endif