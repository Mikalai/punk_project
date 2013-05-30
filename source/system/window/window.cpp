#include <stdio.h>
#include <algorithm>

#include "../errors/module.h"
#include "window.h"
#include "../../math/helper.h"
#include "../event_manager.h"
#include "../logger.h"
#include "../input/module.h"
#include "../timer.h"

namespace System
{

#ifdef _WIN32
	LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	typedef LRESULT WINAPI (*TWindowCallBack)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	int GetX(HWND handle)
	{
		RECT wrect;
		GetClientRect(handle, &wrect);
		return wrect.left;
	}

	int GetY(HWND handle)
	{
		RECT wrect;
		GetClientRect(handle, &wrect);
		return wrect.top;
	}

	int GetWidth(HWND handle)
	{
		RECT rect;
		GetClientRect(handle, &rect);
		return rect.right - rect.left;
	}

	int GetHeight(HWND handle)
	{
		RECT rect;;
		GetClientRect(handle, &rect);
		return rect.bottom - rect.top;
	}

	struct Window::Impl
	{
		HWND m_hwindow;
		bool m_use_parent_window;
		TWindowCallBack m_prev_hwnd_func;

		Impl(WindowAdapter* adapter, const WindowDesc& desc);
		~Impl();
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
		void DrawPixel(int x, int y);
		void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void SwapBuffer();
		operator HWND ();
		LRESULT CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	Window::Impl::Impl(WindowAdapter* adapter, const WindowDesc& desc)
		: m_prev_hwnd_func(DefWindowProc)
	{
		if (desc.m_use_parent_window)
		{
			m_use_parent_window = true;
			m_hwindow = desc.m_hwnd;
			m_prev_hwnd_func = (TWindowCallBack)GetWindowLong(m_hwindow, GWL_WNDPROC);
			SetWindowLongW(m_hwindow, GWL_WNDPROC, (LONG)WindowCallBack);
		}
		else
		{
			m_use_parent_window = false;
			WNDCLASS wc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hIcon = LoadIcon(0, IDI_APPLICATION);
			wc.hInstance = GetModuleHandle(0);
			wc.lpfnWndProc = WindowCallBack;
			wc.lpszClassName = TEXT("Punk Render");
			wc.lpszMenuName = 0;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

			if (!RegisterClass(&wc))
				throw PunkInvalidArgumentException(L"Can't register window class");

			RECT rect;
			rect.left = desc.m_x;
			rect.right = desc.m_x + desc.m_width;
			rect.top = desc.m_y;
			rect.bottom = desc.m_y + desc.m_height;


			DWORD style = WS_OVERLAPPEDWINDOW;
			DWORD styleEx = 0;

			AdjustWindowRectEx(&rect, style, false, styleEx);

			m_hwindow = CreateWindowEx(styleEx, TEXT("Punk Render"), TEXT("Punk Engine"), style,
									   0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0,
									   GetModuleHandle(0), (void*)adapter);

			SetWindowLongPtr(m_hwindow, GWLP_USERDATA, (LONG)adapter);

			if (!m_hwindow)
				throw PunkInvalidArgumentException(L"Can't create window");

			GetClientRect(m_hwindow, &rect);
			ShowWindow(m_hwindow, SW_SHOW);
			UpdateWindow(m_hwindow);
		}
	}

	Window::Impl::~Impl()
	{
		SetWindowLong(m_hwindow, GWL_WNDPROC, (LONG)m_prev_hwnd_func);
		DestroyWindow(m_hwindow);
	}

	int Window::Impl::GetDesktopWidth() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 480;
		return mode.dmPelsWidth;
	}

	int Window::Impl::GetDesktopHeight() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 640;
		return mode.dmPelsHeight;
	}

	int Window::Impl::GetDesktopBitsPerPixel() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 16;
		return mode.dmBitsPerPel;
	}

	int Window::Impl::GetDesktopRefreshRate() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 60;
		return mode.dmDisplayFrequency;
	}

	int Window::Impl::GetWidth() const
	{
		RECT rect;
		GetClientRect(m_hwindow, &rect);
		return rect.right - rect.left;
	}

	int Window::Impl::GetHeight() const
	{
		RECT rect;;
		if (!GetClientRect(m_hwindow, &rect))
			throw PunkInvalidArgumentException(L"Can't get window height");
		//GetWindowRect(m_hwindow, &rect);
		return rect.bottom - rect.top;
	}

	int Window::Impl::GetX() const
	{
		RECT wrect;
		GetClientRect(m_hwindow, &wrect);
		return wrect.left;
	}

	int Window::Impl::GetY() const
	{
		RECT wrect;
		GetClientRect(m_hwindow, &wrect);
		return wrect.top;
	}

	void Window::Impl::SetSize(int width, int height)
	{
		RECT r;
		GetWindowRect(m_hwindow, &r);
		r.right = r.left + width;
		r.bottom = r.top + height;
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
		MoveWindow(m_hwindow, r.left, r.top, width, height, TRUE);
	}

	void Window::Impl::SetPosition(int x, int y)
	{
		RECT r;
		GetWindowRect(m_hwindow, &r);
		MoveWindow(m_hwindow, x, y, r.right - r.left, r.bottom - r.top, TRUE);
	}

	int Window::Impl::Loop()
	{
		if (m_use_parent_window)
			return 0;

		Timer timer;
		timer.Reset();
		MSG msg;
		WindowAdapter* adapter = reinterpret_cast<WindowAdapter*>(GetWindowLongPtr(m_hwindow, GWLP_USERDATA));
		if (!adapter)
			throw PunkInvalidArgumentException(L"Can't get window adapter interface");

		while (1)
		{
			while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
			{
				if (GetMessage(&msg, 0, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					return 0;
				}
			}

			IdleEvent* e = new IdleEvent;
			e->elapsed_time_s = timer.GetElapsedSeconds();
			timer.Reset();
			adapter->WndOnIdleEvent(e);
		}
	}

	void Window::Impl::BreakMainLoop()
	{
		PostQuitMessage(0);
	}

	void Window::Impl::SetTitle(const string& text)
	{
		SetWindowText(m_hwindow, text.Data());
	}

	const string Window::Impl::GetTitle() const
	{
		wchar_t buf[256];
		GetWindowText(m_hwindow, buf, 256);
		return string(buf);
	}

	void Window::Impl::Quite()
	{
		SendMessage(m_hwindow, WM_DESTROY, 0, 0);
	}

	void Window::Impl::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		unsigned char rr = Math::Max((int)r - int(255 - a), 0);
		unsigned char gg = Math::Max((int)g - int(255 - a), 0);
		unsigned char bb = Math::Max((int)b - int(255 - a), 0);

		SetPixel(GetDC(m_hwindow), x, y, RGB( rr, gg, bb));
	}

	void Window::Impl::DrawLine(int x1, int y1, int x2, int y2)
	{
		POINT p;
		MoveToEx(GetDC(m_hwindow), x1, y1, &p);
		LineTo(GetDC(m_hwindow), x2, y2);
		MoveToEx(GetDC(m_hwindow), p.x, p.y, 0);
	}

	void Window::Impl::SwapBuffer()
	{
		SwapBuffers(GetDC(m_hwindow));
	}

	Window::Impl::operator HWND ()
	{
		return m_hwindow;
	}

	LRESULT Window::Impl::CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (m_prev_hwnd_func)
			return m_prev_hwnd_func(hwnd, msg, wParam, lParam);
		else
			return DefWindowProc(hwnd, msg, wParam, lParam);

	}

#endif	//	_WIN32

	Window::Window(WindowAdapter* adapter, const WindowDesc& desc)
		: impl(new Impl(adapter, desc))
	{}

	void Window::SetTitle(const string& text)
	{
		impl->SetTitle(text);
	}

	const string Window::GetTitle() const
	{
		return impl->GetTitle();
	}


	LRESULT Window::CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return impl->CustomDefWindowProc(hwnd, msg, wParam, lParam);
	}

	void Window::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		impl->DrawPixel(x, y, r, g, b, a);
	}

	void Window::SwapBuffer()
	{
		impl->SwapBuffer();
	}

	int Window::GetDesktopBitsPerPixel() const
	{
		return impl->GetDesktopBitsPerPixel();
	}

	int Window::GetDesktopHeight() const
	{
		return impl->GetDesktopHeight();
	}

	int Window::GetDesktopRefreshRate() const
	{
		return impl->GetDesktopRefreshRate();
	}

	int Window::GetDesktopWidth() const
	{
		return impl->GetDesktopWidth();
	}

	void Window::BreakMainLoop()
	{
		impl->BreakMainLoop();
	}

	int Window::Loop()
	{
		return impl->Loop();
	}

	void Window::DrawLine(int x1, int y1, int x2, int y2)
	{
		impl->DrawLine(x1, y1, x2, y2);
	}

	void Window::Quite()
	{
		impl->Quite();
	}

	void Window::SetSize(int width, int height)
	{
		impl->SetSize(width, height);
	}

	void Window::SetPosition(int x, int y)
	{
		impl->SetPosition(x, y);
	}

	int Window::GetX() const
	{
		return impl->GetX();
	}

	int Window::GetY() const
	{
		return impl->GetY();
	}

	int Window::GetWidth() const
	{
		return impl->GetWidth();
	}

	int Window::GetHeight() const
	{
		return impl->GetHeight();
	}

	Window::~Window()
	{
		delete impl;
		impl = nullptr;
	}

#ifdef _WIN32
	Window::operator HWND()
	{
		return *impl;
	}
#endif	//	_WIN32


#ifdef _WIN32

	LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		WindowAdapter* adapter = reinterpret_cast<WindowAdapter*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		/*if (!adapter)
		throw PunkInvalidArgumentException(L"Can't get window adapter interface");*/

		static int x_prev = 0;
		static int y_prev = 0;
		static int x = 0;
		static int y = 0;

		switch (msg)
		{
		case WM_MBUTTONUP:
		{
			MouseMiddleButtonUpEvent* event = new MouseMiddleButtonUpEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, false);
			adapter->WndOnMouseMiddleButtonUpEvent(event);
		}
			break;
		case WM_MBUTTONDOWN:
		{
			MouseMiddleButtonDownEvent* event = new MouseMiddleButtonDownEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, true);
			adapter->WndOnMouseMiddleButtonDownEvent(event);
		}
			break;
		case WM_RBUTTONUP:
		{
			MouseRightButtonUpEvent* event = new MouseRightButtonUpEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, false);
			adapter->WndOnMouseRightButtonUpEvent(event);
		}
			break;
		case WM_RBUTTONDOWN:
		{
			MouseRightButtonDownEvent* event = new MouseRightButtonDownEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, true);
			adapter->WndOnMouseRightButtonDownEvent(event);
		}
			break;
		case WM_LBUTTONUP:
		{
			MouseLeftButtonUpEvent* event = new MouseLeftButtonUpEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, false);
			adapter->WndOnMouseLeftButtonUpEvent(event);
		}
			break;
		case WM_LBUTTONDOWN:
		{
			MouseLeftButtonDownEvent* event = new MouseLeftButtonDownEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, true);
			adapter->WndOnMouseLeftButtonDownEvent(event);
		}
			break;
		case WM_MOUSEHOVER:
		{
			MouseHooverEvent* event = new MouseHooverEvent;
			event->x = LOWORD(lParam);
			event->y = GetHeight(hwnd) - HIWORD(lParam);
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			adapter->WndOnMouseHooverEvent(event);
		}
			break;
		case WM_MOUSEMOVE:
		{
			MouseMoveEvent* event = new MouseMoveEvent;

			x_prev = x;
			y_prev = y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			event->x = x;
			event->y = GetHeight(hwnd) - y;
			event->x_prev = x_prev;
			event->y_prev = GetHeight(hwnd) - y_prev;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;

			if (Mouse::Instance()->IsLocked())
			{
				RECT r, r2;
				GetWindowRect(hwnd, &r);
				GetClientRect(hwnd, &r2);
				int c_x = (r.left + r.right) / 2;
				int c_y = (r.top + r.bottom) / 2;
				POINT p = {c_x, c_y};
				ClientToScreen(hwnd, &p);
				if (x != x_prev || y != y_prev)
				{
					x = x_prev = c_x;
					y = y_prev = c_y;
					SetCursorPos(p.x, p.y);
				}
			}

			TRACKMOUSEEVENT te;
			memset(&te, 0, sizeof(te));
			te.cbSize = sizeof(te);
			te.dwFlags = TME_HOVER;
			te.dwHoverTime = 400;
			te.hwndTrack = hwnd;
			TrackMouseEvent(&te);
			adapter->WndOnMouseMoveEvent(event);
		}
			break;
		case WM_MOUSEWHEEL:
		{
			POINT p = {LOWORD(lParam), HIWORD(lParam)};
			ScreenToClient(hwnd, &p);
			MouseWheelEvent* event = new MouseWheelEvent;
			event->x = p.x;
			event->y = GetHeight(hwnd) - p.y;
			event->x_prev = x_prev;
			event->y_prev = y_prev;
			x_prev = event->x;
			y_prev = event->y;
			event->delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
			event->controlKey = (wParam & MK_CONTROL) != 0;
			event->leftButton = (wParam & MK_LBUTTON) != 0;
			event->middleButton = (wParam & MK_MBUTTON) != 0;
			event->rightButton = (wParam & MK_RBUTTON) != 0;
			event->shiftButton = (wParam & MK_SHIFT) != 0;
			event->xbutton1 = (wParam & MK_XBUTTON1) != 0;
			event->xbutton2 = (wParam & MK_XBUTTON2) != 0;
			adapter->WndOnMouseWheelEvent(event);
		}
			break;
		case WM_CHAR:
		{
			KeyCharEvent* event = new KeyCharEvent;
			event->key = (int)wParam;
			event->repeat_count = (lParam & 0xFFFF) != 0;
			event->scan_code = (lParam & 0xFF0000) != 0;
			event->isExtended = (lParam & 0x1000000) != 0;
			event->isAltPressed = (lParam & 0x20000000) != 0;
			event->prevState = (lParam & 0x40000000) != 0;
			event->transitionState = (lParam & 0x80000000) != 0;
			adapter->WndOnCharEvent(event);
		}
			break;
		case WM_UNICHAR:
		{
			KeyWCharEvent* event = new KeyWCharEvent;
			event->key = (int)wParam;
			event->repeat_count = (lParam & 0xFFFF) != 0;
			event->scan_code = (lParam & 0xFF0000) != 0;
			event->isExtended = (lParam & 0x1000000) != 0;
			event->isAltPressed = (lParam & 0x20000000) != 0;
			event->prevState = (lParam & 0x40000000) != 0;
			event->transitionState = (lParam & 0x80000000) != 0;
			adapter->WndOnWideCharEvent(event);
		}
			break;
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			KeyDownEvent* event = new KeyDownEvent;
			event->key = (int)wParam;
			event->repeat_count = (lParam & 0xFFFF) != 0;
			event->scan_code = (lParam & 0xFF0000) != 0;
			event->isExtended = (lParam & 0x1000000) != 0;
			event->prevState = (lParam & 0x40000000) != 0;
			event->transitionState = (lParam & 0x80000000) != 0;
			Keyboard::Instance()->SetKeyState(wParam, true);
			adapter->WndOnKeyDownEvent(event);
			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			KeyUpEvent* event = new KeyUpEvent;
			event->key = (int)wParam;
			Keyboard::Instance()->SetKeyState(wParam, false);
			adapter->WndOnKeyUpEvent(event);
			break;
		}
		case WM_SIZE:
		{
			WindowResizeEvent* event = new WindowResizeEvent;
			event->minimized = (wParam & SIZE_MINIMIZED) != 0;
			event->restored = (wParam & SIZE_RESTORED) != 0;
			event->width = LOWORD(lParam);
			event->height = HIWORD(lParam);
			adapter->WndOnResizeEvent(event);

			/*		RECT r;
				GetWindowRect(window->m_hwindow, &r);
				x_prev = (r.left + r.right)/2;
				y_prev = (r.top + r.bottom)/2;
				SetCursorPos((r.left+r.right)/2, (r.top+r.bottom)/2);*/
		}
			break;
		case WM_CREATE:
		{
			//MessageBoxA(0, "sdfg", "SDFG", MB_OK);
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			RECT r;
			GetWindowRect(hwnd, &r);
			x_prev = (r.left + r.right)/2;
			y_prev = (r.top + r.bottom)/2;
			SetCursorPos((r.left+r.right)/2, (r.top+r.bottom)/2);
			auto a = reinterpret_cast<WindowAdapter*>(cs->lpCreateParams);
			a->WndOnCreateEvent();
		}
			break;
		case WM_DESTROY:
			adapter->WndOnDestroyEvent();
			PostQuitMessage(0);			
			break;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
#endif	//	_WIN32

}
