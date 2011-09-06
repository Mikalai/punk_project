/*
	ile: manager.h
	uthor: Mikalai Abramau
	esc: gui manager
*/

#ifndef _H_PUNK_GUI_MANAGER
#define _H_PUNK_GUI_MANAGER

#include "widget.h"
#include "../system/events/events.h"
#include "../system/window.h"
#include "../driver/video/opengl/glsl_program.h"

#include <vector>

namespace GUI
{

	class Manager
	{
		static Driver::GLSLProgram program;
		static System::Window* desktop;

		std::vector<Widget*> rootWidgets;
		Widget* m_focusWidget;

	public:
		Manager(System::Window* wnd);
		~Manager();

		void AddRootWidget(Widget* widget);
		void RemoveRootWidget(Widget* widget);
		void Update(System::Event* event);

		void EventHandler(System::Event* event);

		void SendChildren(System::Event* event);  
	};
}

#endif