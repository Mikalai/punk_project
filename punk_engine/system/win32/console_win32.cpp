#include <cstdio>
#include "console_win32.h"

namespace System
{
	SingletoneImplementation(Console);

	void Console::Print(const string& text)
	{
		wprintf_s(L"%s", text.Data());
	}

	Console::Console()
	{
		hConsole = 0;
		textColor = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
		backColor = 0;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		/*pos.X = 0;
		pos.Y = 0;
		SMALL_RECT rec;
		rec.Left = 10;
		rec.Right = 75;
		rec.Top = 10;
		rec.Bottom = 60;
		SetConsoleWindowInfo(hConsole, TRUE, &rec);*/
	}

	void Console::SetPosition(int x, int y)
	{
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hConsole, pos);
	}

	void Console::Clear()
	{
		char buf[] = "                                                                     ";
		SetPosition(0,0);
		for (int i = 0; i < 80; i++)
		{
			SetPosition(0,i);
			puts(buf);
		}
	}

	void Console::SetTextColor(Color col)
	{
		switch(col)
		{
		case COLOR_BLACK:
			textColor = 0;
			break;
		case COLOR_BLUE:
			textColor = FOREGROUND_BLUE;
			break;
		case COLOR_GREEN:
			textColor = FOREGROUND_GREEN;
			break;
		case COLOR_CYAN:
			textColor = FOREGROUND_BLUE|FOREGROUND_GREEN;
			break;
		case COLOR_RED:
			textColor = FOREGROUND_RED;
			break;
		case COLOR_MAGENTA:
			textColor = FOREGROUND_BLUE|FOREGROUND_RED;
			break;
		case COLOR_BROWN:
			textColor = FOREGROUND_RED|FOREGROUND_GREEN;
			break;
		case COLOR_LIGHTGRAY:
			textColor = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;//|FOREGROUND_INTENSITY;
			break;
		case COLOR_DARKGRAY:
			textColor = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
			break;
		case COLOR_LIGHTBLUE:
			textColor = FOREGROUND_BLUE|FOREGROUND_INTENSITY;
			break;
		case COLOR_LIGHTGREEN:
			textColor = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
			break;
		case COLOR_LIGHTCYAN:
			textColor = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
			break;
		case COLOR_LIGHTRED:
			textColor = FOREGROUND_RED|FOREGROUND_INTENSITY;
			break;
		case COLOR_LIGHTMAGENTA:
			textColor = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY;
			break;
		case COLOR_WHITE:
			textColor = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
			break;
		case COLOR_YELLOW:
			textColor = FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
			break;

		}
		SetConsoleTextAttribute(hConsole, textColor|backColor);
	}

	void Console::SetBackColor(Color col)
	{
		switch(col)
		{
		case COLOR_BLACK:
			backColor = 0;
			break;
		case COLOR_BLUE:
			backColor = BACKGROUND_BLUE;
			break;
		case COLOR_GREEN:
			backColor = BACKGROUND_GREEN;
			break;
		case COLOR_CYAN:
			backColor = BACKGROUND_BLUE|BACKGROUND_GREEN;
			break;
		case COLOR_RED:
			backColor = BACKGROUND_RED;
			break;
		case COLOR_MAGENTA:
			backColor = BACKGROUND_BLUE|BACKGROUND_RED;
			break;
		case COLOR_BROWN:
			backColor = BACKGROUND_RED|BACKGROUND_GREEN;
			break;
		case COLOR_LIGHTGRAY:
			backColor = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;//|FOREGROUND_INTENSITY;
			break;
		case COLOR_DARKGRAY:
			backColor = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;
			break;
		case COLOR_LIGHTBLUE:
			backColor = BACKGROUND_BLUE|BACKGROUND_INTENSITY;
			break;
		case COLOR_LIGHTGREEN:
			backColor = BACKGROUND_GREEN|BACKGROUND_INTENSITY;
			break;
		case COLOR_LIGHTCYAN:
			backColor = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
			break;
		case COLOR_LIGHTRED:
			backColor = BACKGROUND_RED|BACKGROUND_INTENSITY;
			break;
		case COLOR_LIGHTMAGENTA:
			backColor = BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY;
			break;
		case COLOR_WHITE:
			backColor = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY;
			break;
		case COLOR_YELLOW:
			backColor = BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY;
			break;
		}
		SetConsoleTextAttribute(hConsole, textColor|backColor);
	}
}