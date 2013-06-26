#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#elif defined __gnu_linux__
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#endif

#include <iostream>
#include <cstdio>
#include <clocale>
#include "console.h"

namespace System
{
	struct Console::Impl
	{
#ifdef _WIN32
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
#elif defined __gnu_linux__
        int m_x, m_y;
#endif

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
#ifdef _WIN32
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
#elif defined __gnu_linux__
#endif
	}

	//	set new cursor position in console
	void Console::Impl::SetPosition(int x, int y)
    {
#ifdef _WIN32
		if (m_console_handle)
		{
			m_cursor_position.X = x;
			m_cursor_position.Y = y;
			SetConsoleCursorPosition(m_console_handle, m_cursor_position);
		}
#elif defined __gnu_linux__
        std::cout << "\33[" << x << ":" << y << "H";
#endif
	}
	//	set new text color
	void Console::Impl::SetTextColor(Color col)
	{
#ifdef _WIN32
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
#elif defined __gnu_linux__
        switch(col)
        {
        case COLOR_BLACK:
            std::cout << "\033[0;30m";
            break;
        case COLOR_BLUE:
            std::cout << "\033[0;34m";
            break;
        case COLOR_GREEN:
            std::cout << "\033[0;32m";
            break;
        case COLOR_CYAN:
            std::cout << "\033[0;36m";
            break;
        case COLOR_RED:
            std::cout << "\033[0;31m";
            break;
        case COLOR_MAGENTA:
            std::cout << "\033[0;35m";
            break;
        case COLOR_BROWN:
            std::cout << "\033[0;33m";
            break;
        case COLOR_LIGHTGRAY:
            std::cout << "\033[0;37m";
            break;
        case COLOR_DARKGRAY:
            std::cout << "\033[0m";
            break;
        case COLOR_LIGHTBLUE:
            std::cout << "\033[0m";
            break;
        case COLOR_LIGHTGREEN:
            std::cout << "\033[0m";
            break;
        case COLOR_LIGHTCYAN:
            std::cout << "\033[0m";
            break;
        case COLOR_LIGHTRED:
            std::cout << "\033[0m";
            break;
        case COLOR_LIGHTMAGENTA:
            std::cout << "\033[0m";
            break;
        case COLOR_WHITE:
            std::cout << "\033[0m";
            break;
        case COLOR_YELLOW:
            std::cout << "\033[0m";
            break;
        }
#endif

	}

	//	set new back color
	void Console::Impl::SetBackColor(Color col)
	{
#ifdef _WIN32
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
#elif defined __gnu_linux__
        switch(col)
        {
        case COLOR_BLACK:
            std::cout << "\033[7;30m";
            break;
        case COLOR_BLUE:
            std::cout << "\033[7;34m";
            break;
        case COLOR_GREEN:
            std::cout << "\033[7;32m";
            break;
        case COLOR_CYAN:
            std::cout << "\033[7;36m";
            break;
        case COLOR_RED:
            std::cout << "\033[7;31m";
            break;
        case COLOR_MAGENTA:
            std::cout << "\033[7;35m";
            break;
        case COLOR_BROWN:
            std::cout << "\033[7;33m";
            break;
        case COLOR_LIGHTGRAY:
            std::cout << "\033[7;37m";
            break;
        case COLOR_DARKGRAY:
            std::cout << "\033[7m";
            break;
        case COLOR_LIGHTBLUE:
            std::cout << "\033[7m";
            break;
        case COLOR_LIGHTGREEN:
            std::cout << "\033[7m";
            break;
        case COLOR_LIGHTCYAN:
            std::cout << "\033[7m";
            break;
        case COLOR_LIGHTRED:
            std::cout << "\033[7m";
            break;
        case COLOR_LIGHTMAGENTA:
            std::cout << "\033[7m";
            break;
        case COLOR_WHITE:
            std::cout << "\033[7m";
            break;
        case COLOR_YELLOW:
            std::cout << "\033[7m";
            break;
        }
#endif
	}

	//	retreive console screen buffer width
	int Console::Impl::GetScreenBufferWidth() const
	{
#ifdef _WIN32
		return m_screen_info.dwSize.X;
#elif defined __gnu_linux__
        winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
#endif
	}
	//	retrieve console screen buffer height
	int Console::Impl::GetScreenBufferHeight() const
	{
#ifdef _WIN32
		return m_screen_info.dwSize.Y;
#elif defined __gnu_linux__
        winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
#endif
	}
	//	retrieve visible width of the console screen
	int Console::Impl::GetViewportWidth()
	{
#ifdef _WIN32
		GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
		return m_screen_info.srWindow.Right - m_screen_info.srWindow.Left;
		//return m_screen_info.dwMaximumWindowSize.X;
#elif defined __gnu_linux__
        winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
#endif
	}
	//	retrieve visisble height of the console screen
	int Console::Impl::GetViewportHeight()
	{
#ifdef _WIN32
		GetConsoleScreenBufferInfo(m_console_handle, &m_screen_info);
		return m_screen_info.srWindow.Bottom - m_screen_info.srWindow.Top;
		//return m_screen_info.dwMaximumWindowSize.Y;
#elif defined __gnu_linux__
        winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
#endif
	}
	//	fills console with back color
	void Console::Impl::Clear()
	{
#ifdef _WIN32
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
#elif defined __gnu_linux__
        std::cout << "\033[2j";
#endif
	}

	std::ostream& Console::Impl::Write()
	{
		return std::cout;
	}

	std::istream& Console::Impl::Read()
	{
		return std::cin;
	}


	//
	//	Console implementation goes here
	//
	Console::Console()
		: impl(new Impl)
	{}

    Console::~Console()
    {
        delete impl;
        impl = nullptr;
    }

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
