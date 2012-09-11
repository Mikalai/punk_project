#ifndef _H_GUI_CONTROL
#define _H_GUI_CONTROL

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

	std::auto_ptr<GUI::Manager> m_gui_manager;
public:

	GUIControl()
	{
		m_gui_manager.reset(new GUI::Manager);
		std::auto_ptr<GUI::Widget> player_control_width(new GUI::Widget(0, 0, 1, 0.1));
		player_control_width->SetText(L"");
		m_gui_manager->AddRootWidget(player_control_width.release());
	}

	void Render()
	{
		m_gui_manager->Render();
	}
};

#endif	//	_H_GUI_CONTROL