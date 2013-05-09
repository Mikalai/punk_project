#ifndef _H_PUNK_SYSTEM_WINDOW
#define _H_PUNK_SYSTEM_WINDOW

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#endif	//	_WIN32

#include "window_adapter.h"
#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	class PUNK_ENGINE Window
	{	
	public:
		Window(WindowAdapter* adapter, const WindowDesc& desc = WindowDesc());
		~Window();
		int GetDesktopWidth() const;
		int GetDesktopHeight() const;
		int GetDesktopBitsPerPixel() const;
		int GetDesktopRefreshRate() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		void SetSize(int width, int height);
		void SetPosition(int x, int y);
		int Loop();
		void BreakMainLoop();
		void SetTitle(const string& text);
		const string GetTitle() const;
		void Quite();
		void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void SwapBuffer();		       

#ifdef _WIN32
        LRESULT CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		operator HWND ();
#endif
		struct Impl;
		Impl* impl;		
	};
}

#endif	//_H_PUNK_SYSTEM_WINDOW
