#ifndef _H_GUI_CONTROL
#define _H_GUI_CONTROL

#include <set>
#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"
#include "../punk_engine/logic/logic.h"
#include "../punk_engine/render/render.h"

class GUIControl
{
	static const int PLAYER_CONTROL = 1;
	static const int BUILD_WINDOW = 2;
	static const int BUILD_DETAIL_WINDOW = 3;

	std::set<int> m_active_window;
	std::auto_ptr<GUI::Manager> m_gui_manager;

	GUI::Widget* player_control_window;
	GUI::Widget* build_window;
	GUI::Button* build_button;
public:

	GUIControl()
	{
		m_gui_manager.reset(new GUI::Manager);
		player_control_window = new GUI::Widget(0, 0, 1, 0.05);
		build_button = new GUI::Button(0, 0, 0.1, 1, L"Build", player_control_window);
		build_button->SetMouseLeftClickHandler(System::EventHandler(this, &GUIControl::OnBuildButtonClick));
		build_window = new GUI::Widget(0, 0.05, 0.2, 1, 0);
		build_window->Show(false);
		//player_control_window->AddChild(build_button);
		m_gui_manager->AddRootWidget(player_control_window);
		m_gui_manager->AddRootWidget(build_window);
	}

	void OnBuildButtonClick(System::Event*)
	{
		build_window->Show(!build_window->IsVisible());
	}

	void Render()
	{		
		m_gui_manager->Render();
	}

	~GUIControl()
	{
//		delete player_control_window;
	}
};

#endif	//	_H_GUI_CONTROL