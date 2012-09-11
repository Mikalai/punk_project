#include <cstdio>
#include <clocale>
#include "console_win32.h"

namespace System
{
	//
	//	Console implementation goes here
	//
	Console::Console()
	{
		m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (m_console_handle)
		{
			setlocale(LC_CTYPE, "Russian");			
			m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
			m_back_color = 0;		
			GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
			SetBackColor(COLOR_BLACK);
			Clear();
		}
	}

	void Console::SetPosition(int x, int y)
	{
		if (m_console_handle)
		{
			m_cursor_position.X = x;
			m_cursor_position.Y = y;
			SetConsoleCursorPosition(m_console_handle, m_cursor_position);
		}
	}

	void Console::Clear()
	{
		if (m_console_handle)
		{
			static const int SIZE = 32768;
			char buf[SIZE];
			memset(buf, ' ', sizeof(buf)/sizeof(buf[0])); 
			int to_fill = m_screen_info.dwSize.X*m_screen_info.dwSize.Y;				
			int res = 0;
			DWORD written = 0;
			SetPosition(0,0);		
			while (to_fill > 0)
			{					
				res = WriteConsoleA(m_console_handle, buf, SIZE, &written, 0);		
				to_fill -= written;
			}		
			SetPosition(0,0);
		}
	}

	void Console::SetTextColor(Color col)
	{
		if (m_console_handle)
		{
			switch(col)
			{
			case COLOR_BLACK:
				m_text_color = 0;
				break;
			case COLOR_BLUE:
				m_text_color = FOREGROUND_BLUE;
				break;
			case COLOR_GREEN:
				m_text_color = FOREGROUND_GREEN;
				break;
			case COLOR_CYAN:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN;
				break;
			case COLOR_RED:
				m_text_color = FOREGROUND_RED;
				break;
			case COLOR_MAGENTA:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_RED;
				break;
			case COLOR_BROWN:
				m_text_color = FOREGROUND_RED|FOREGROUND_GREEN;
				break;
			case COLOR_LIGHTGRAY:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;//|FOREGROUND_INTENSITY;
				break;
			case COLOR_DARKGRAY:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
				break;
			case COLOR_LIGHTBLUE:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_INTENSITY;
				break;
			case COLOR_LIGHTGREEN:
				m_text_color = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
				break;
			case COLOR_LIGHTCYAN:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
				break;
			case COLOR_LIGHTRED:
				m_text_color = FOREGROUND_RED|FOREGROUND_INTENSITY;
				break;
			case COLOR_LIGHTMAGENTA:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY;
				break;
			case COLOR_WHITE:
				m_text_color = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
				break;
			case COLOR_YELLOW:
				m_text_color = FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
				break;

			}
			SetConsoleTextAttribute(m_console_handle, m_text_color|m_back_color);
		}
	}

	void Console::SetBackColor(Color col)
	{
		if (m_console_handle)
		{
			switch(col)
			{
			case COLOR_BLACK:
				m_back_color = 0;
				break;
			case COLOR_BLUE:
				m_back_color = BACKGROUND_BLUE;
				break;
			case COLOR_GREEN:
				m_back_color = BACKGROUND_GREEN;
				break;
			case COLOR_CYAN:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_GREEN;
				break;
			case COLOR_RED:
				m_back_color = BACKGROUND_RED;
				break;
			case COLOR_MAGENTA:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_RED;
				break;
			case COLOR_BROWN:
				m_back_color = BACKGROUND_RED|BACKGROUND_GREEN;
				break;
			case COLOR_LIGHTGRAY:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;//|FOREGROUND_INTENSITY;
				break;
			case COLOR_DARKGRAY:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;
				break;
			case COLOR_LIGHTBLUE:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_INTENSITY;
				break;
			case COLOR_LIGHTGREEN:
				m_back_color = BACKGROUND_GREEN|BACKGROUND_INTENSITY;
				break;
			case COLOR_LIGHTCYAN:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
				break;
			case COLOR_LIGHTRED:
				m_back_color = BACKGROUND_RED|BACKGROUND_INTENSITY;
				break;
			case COLOR_LIGHTMAGENTA:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY;
				break;
			case COLOR_WHITE:
				m_back_color = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY;
				break;
			case COLOR_YELLOW:
				m_back_color = BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY;
				break;
			}
			SetConsoleTextAttribute(m_console_handle, m_text_color|m_back_color);
		}
	}

	Console* Console::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new Console);
		return m_instance.get();
	}

	void Console::Destroy()
	{
		m_instance.reset(0);
	}

	std::auto_ptr<Console> Console::m_instance;

}