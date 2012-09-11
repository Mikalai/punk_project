#include "main_menu.h"

MainMenu::MainMenu(float x, float y, float width, float height, GUI::Widget* parent)
	: GUI::Widget(x, y, width, height, L"", parent)
{
	btn_start_resume_game = new GUI::Button(0, 1-0.3, 1, 0.3, L"Start", this);
	btn_start_resume_game->SetTextSize(48);
	btn_records = new GUI::Button(0, 1-0.6, 1, 0.3, L"Records", this);
	btn_records->SetTextSize(48);
	btn_quit = new GUI::Button(0, 1-0.9, 1, 0.3, L"Quit", this);
	btn_quit->SetTextSize(48);
}

void MainMenu::OnStartResumeClick(System::Handler h)
{
	btn_start_resume_game->SetMouseLeftClickHandler(h);
}

void MainMenu::OnQuitClick(System::Handler h)
{
	btn_quit->SetMouseLeftClickHandler(h);
}

