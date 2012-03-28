#ifndef _H_SYSTEM_CONSOLE_WIN32
#define _H_SYSTEM_CONSOLE_WIN32

#include <Windows.h>
#include "../singletone.h"
#include "string_win32.h"
#include "../config.h"

namespace System
{
	SingletoneInterface(Console, MODULE_SYSTEM);

	class MODULE_SYSTEM Console : public Singletone(Console)
	{
		HANDLE hConsole;
		COORD pos;
		WORD textColor;
		WORD backColor;

		Console(const Console&);
		Console& operator = (const Console&);
	public:

		typedef enum {COLOR_BLACK, 
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_CYAN,
		COLOR_RED,
		COLOR_MAGENTA,
		COLOR_BROWN,
		COLOR_LIGHTGRAY,
		COLOR_DARKGRAY,
		COLOR_LIGHTBLUE,
		COLOR_LIGHTGREEN,
		COLOR_LIGHTCYAN,
		COLOR_LIGHTRED,
		COLOR_LIGHTMAGENTA,
		COLOR_YELLOW,
		COLOR_WHITE} Color;

		Console();
		void SetPosition(int x, int y);
		void SetTextColor(Color col);
		void SetBackColor(Color col);
		void Print(const string& text);
		void Clear();
	};
}

#endif