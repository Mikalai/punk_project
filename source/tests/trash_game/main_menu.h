#ifndef _H_MAIN_MENU
#define _H_MAIN_MENU

#include "../../gui/gui.h"

class MainMenu : public GUI::Widget
{
	GUI::Button* btn_start_resume_game;
	GUI::Button* btn_records;
	GUI::Button* btn_quit;
public:
	MainMenu(float x = 0, float y = 0, float width = 1, float height = 1, GUI::Widget* parent = 0);
	void OnStartResumeClick(System::Handler handler);
	void OnQuitClick(System::Handler handler);	
};

#endif