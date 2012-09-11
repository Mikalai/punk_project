#ifndef _H_SYSTEM_CONSOLE_WIN32
#define _H_SYSTEM_CONSOLE_WIN32


#include <Windows.h>
#include <memory>
#include "../singletone.h"
#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	SingletoneInterface(Console, PUNK_ENGINE);

	class PUNK_ENGINE Console : public Singletone(Console)
	{
		//	handle of the console object
		HANDLE m_console_handle;
		//	current cursor position
		COORD m_cursor_position;
		//	selected text color
		WORD m_text_color;
		//	selected back color
		WORD m_back_color;
		//	information of the console screen buffer
		CONSOLE_SCREEN_BUFFER_INFO m_screen_info;
		//	copy constructor denied
		Console(const Console&);
		//	copy operator denied
		Console& operator = (const Console&);
		//	no public constructor
		Console();
		//	instance of the console is stored here
		static std::auto_ptr<Console> m_instance;

	public:

		//	possible colors that can be use in console
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

		//	set new cursor position in console
		void SetPosition(int x, int y);
		//	set new text color 
		void SetTextColor(Color col);
		//	set new back color
		void SetBackColor(Color col);
		//	retreive console screen buffer width
		int GetScreenBufferWidth() const { return m_screen_info.dwSize.X; }
		//	retrieve console screen buffer height
		int GetScreenBufferHeight() const { return m_screen_info.dwSize.Y; }
		//	retrieve visible width of the console screen
		int GetViewportWidth() 
		{
			GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
			return m_screen_info.srWindow.Right - m_screen_info.srWindow.Left;
			//return m_screen_info.dwMaximumWindowSize.X; 
		}
		//	retrieve visisble height of the console screen
		int GetViewportHeight() 
		{
			GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
			return m_screen_info.srWindow.Bottom - m_screen_info.srWindow.Top;
			//return m_screen_info.dwMaximumWindowSize.Y; 
		}
		//	fills console with back color
		void Clear();
		//	retrieve single instance of the console
		static Console* Instance();
		//	destroys console
		static void Destroy();
	};
}

#endif