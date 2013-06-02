#ifndef _H_SYSTEM_CONSOLE
#define _H_SYSTEM_CONSOLE

#include <memory>
#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE_API Console
	{
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
		int GetScreenBufferWidth() const;
		//	retrieve console screen buffer height
		int GetScreenBufferHeight()const;
		//	retrieve visible width of the console screen
		int GetViewportWidth();
		//	retrieve visisble height of the console screen
		int GetViewportHeight();
		//	fills console with back color
		void Clear();
		//	retrieve single instance of the console
		static Console* Instance();
		//	destroys console
		static void Destroy();

		struct Impl;
		Impl* impl;

		std::ostream& Write();
		std::istream& Read();

	private:
		//	copy constructor denied
		Console(const Console&);
		//	copy operator denied
		Console& operator = (const Console&);
		//	no public constructor
		Console();
		//	instance of the console is stored here
		static std::unique_ptr<Console> m_instance;
	};
}

#endif	//	_H_SYSTEM_CONSOLE
