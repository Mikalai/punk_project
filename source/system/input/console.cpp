#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#endif	//	_WIN32

#include <iostream>
#include <cstdio>
#include <clocale>
#include "console.h"

namespace System
{
#ifdef _WIN32

	struct Console::Impl
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

		Impl();
		void SetPosition(int x, int y);
		void SetTextColor(Color col);
		void SetBackColor(Color col);
		int GetScreenBufferWidth() const;
		int GetScreenBufferHeight() const;
		int GetViewportWidth();
		int GetViewportHeight();
		void Clear();
		std::ostream& Write();
		std::istream& Read();
	};

	Console::Impl::Impl()
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

	//	set new cursor position in console
	void Console::Impl::SetPosition(int x, int y)
	{
		if (m_console_handle)
		{
			m_cursor_position.X = x;
			m_cursor_position.Y = y;
			SetConsoleCursorPosition(m_console_handle, m_cursor_position);
		}
	}
	//	set new text color
	void Console::Impl::SetTextColor(Color col)
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

	//	set new back color
	void Console::Impl::SetBackColor(Color col)
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

	//	retreive console screen buffer width
	int Console::Impl::GetScreenBufferWidth() const
	{
		return m_screen_info.dwSize.X;
	}
	//	retrieve console screen buffer height
	int Console::Impl::GetScreenBufferHeight() const
	{
		return m_screen_info.dwSize.Y;
	}
	//	retrieve visible width of the console screen
	int Console::Impl::GetViewportWidth()
	{
		GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
		return m_screen_info.srWindow.Right - m_screen_info.srWindow.Left;
		//return m_screen_info.dwMaximumWindowSize.X;
	}
	//	retrieve visisble height of the console screen
	int Console::Impl::GetViewportHeight()
	{
		GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
		return m_screen_info.srWindow.Bottom - m_screen_info.srWindow.Top;
		//return m_screen_info.dwMaximumWindowSize.Y;
	}
	//	fills console with back color
	void Console::Impl::Clear()
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
                if (!res)
                    break;
				to_fill -= written;
			}
			SetPosition(0,0);
		}
	}

	std::ostream& Console::Impl::Write()
	{
		return std::cout;
	}

	std::istream& Console::Impl::Read()
	{
		return std::cin;
	}

#endif	//	_WIN32

	//
	//	Console implementation goes here
	//
	Console::Console()
		: impl(new Impl)
	{}

	void Console::SetPosition(int x, int y)
	{
		impl->SetPosition(x, y);
	}

	void Console::Clear()
	{
		impl->Clear();
	}

	void Console::SetTextColor(Color col)
	{
		impl->SetTextColor(col);
	}

	void Console::SetBackColor(Color col)
	{
		impl->SetBackColor(col);
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

	std::unique_ptr<Console> Console::m_instance;
}
