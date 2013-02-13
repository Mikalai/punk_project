#ifdef _WIN32

#include <stdio.h>
#include <algorithm>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "../../errors/module.h"
#include "window_win32.h"
#include "../../../math/helper.h"
#include "../../event_manager.h"
#include "../../logger.h"
#include "../../win32/timer_win32.h"
#include "../../win32/keyboard_win32.h"
#include "../../win32/mouse_win32.h"

namespace System
{
	LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

	Window::Window(WindowAdapter* adapter, const WindowDesc& desc)
	{
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

		m_windowHandle = CreateWindowEx(styleEx, TEXT("Punk Render"), TEXT("Punk Engine"), style,
			0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0, GetModuleHandle(0), (void*)adapter);

		SetWindowLongPtr(m_windowHandle, GWLP_USERDATA, (LONG)adapter);

		if (!m_windowHandle)
			throw PunkInvalidArgumentException(L"Can't create window");

		GetClientRect(m_windowHandle, &rect);
		ShowWindow(m_windowHandle, SW_SHOW);
		UpdateWindow(m_windowHandle);
	}

	void Window::SetTitle(const string& text)
	{
		SetWindowText(m_windowHandle, text.Data());
	}

	string Window::GetTitle() const
	{
		wchar_t buf[256];
		GetWindowText(m_windowHandle, buf, 256);
		return string(buf);
	}

	void Window::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		unsigned char rr = Math::Max((int)r - int(255 - a), 0);
		unsigned char gg = Math::Max((int)g - int(255 - a), 0);
		unsigned char bb = Math::Max((int)b - int(255 - a), 0);

		SetPixel(GetDC(m_windowHandle), x, y, RGB( rr, gg, bb));
	}

	void Window::SwapBuffer()
	{
		SwapBuffers(GetDC(m_windowHandle));
	}

	int Window::GetDesktopBitsPerPixel() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 16;
		return mode.dmBitsPerPel;
	}

	int Window::GetDesktopHeight() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 640;
		return mode.dmPelsHeight;
	}

	int Window::GetDesktopRefreshRate() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 60;
		return mode.dmDisplayFrequency;
	}

	int Window::GetDesktopWidth() const
	{
		DEVMODE mode;
		memset(&mode, 0, sizeof(mode));
		mode.dmSize = sizeof(mode);

		if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
			return 480;
		return mode.dmPelsWidth;
	}

	void Window::BreakMainLoop()
	{
		PostQuitMessage(0);
	}

	int Window::Loop()
	{
		Timer timer;
		timer.UpdateStartPoint();
		MSG msg;
		WindowAdapter* adapter = reinterpret_cast<WindowAdapter*>(GetWindowLongPtr(m_windowHandle, GWLP_USERDATA));
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

			//Sleep(10);
			IdleEvent* e = new IdleEvent;
			e->elapsed_time_s = timer.GetElapsedTime();
			timer.UpdateStartPoint();
			adapter->OnIdleEvent(e);
			
			/****************************************
			//EventManager::Instance()->FixEvent(e);
			//EventManager::Instance()->Process();			
			/****************************************

			/*std::multimap<UINT, Handler>::iterator lb = m_handlers.lower_bound(WM_IDLE);
			std::multimap<UINT, Handler>::iterator ub = m_handlers.upper_bound(WM_IDLE);
			for (std::multimap<UINT, Handler>::iterator i = lb; i != ub; i++)
			{
			(*i).second(Parameters(0, WM_IDLE, 0, 0));
			}/**/
		}
	}

	void Window::DrawLine(int x1, int y1, int x2, int y2)
	{
		POINT p;
		MoveToEx(GetDC(m_windowHandle), x1, y1, &p);
		LineTo(GetDC(m_windowHandle), x2, y2);
		MoveToEx(GetDC(m_windowHandle), p.x, p.y, 0);
	}

	void Window::Quite()
	{
		SendMessage(m_windowHandle, WM_DESTROY, 0, 0);
	}

	/*	void Window::SubscribeHandler(unsigned message, Handler handler)
	{
	Logger::Instance()->WriteDebugMessage(string::Format(L"[WINDOW] => something subscribed for %d", message));
	EventManager::Instance()->SubscribeHandler(message, handler);
	}

	void Window::UnsubscribeHandler(unsigned message, Handler handler)
	{
	EventManager::Instance()->UnsubscribeHandler(message, handler);
	/*std::multimap<unsigned, Handler>::iterator lb = m_handlers.lower_bound(message);
	std::multimap<unsigned, Handler>::iterator ub = m_handlers.upper_bound(message);
	std::multimap<unsigned, Handler>::iterator at = m_handlers.end();
	for (std::multimap<unsigned, Handler>::iterator i = lb; i != ub; i++)
	{
	if ((*i).second == handler)
	{
	at = i;
	break;
	}
	}
	if (at != m_handlers.end())
	{
	m_handlers.erase(at);
	}
	else
	throw SystemError("Handler was not subscribed");*/
	/*}*/

	Window::~Window()
	{
		DestroyWindow(m_windowHandle);
		//   m_handlers.clear();
	}

	Window::operator HWND()
	{
		return m_windowHandle;
	}

	void Window::SetSize(int width, int height)
	{
		RECT r;
		GetWindowRect(m_windowHandle, &r);
		r.right = r.left + width;
		r.bottom = r.top + height;
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
		MoveWindow(m_windowHandle, r.left, r.top, width, height, TRUE);
	}

	void Window::SetPosition(int x, int y)
	{
		RECT r;
		GetWindowRect(m_windowHandle, &r);
		MoveWindow(m_windowHandle, x, y, r.right - r.left, r.bottom - r.top, TRUE);
	}

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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, false);
				adapter->OnMouseMiddleButtonUpEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::MIDDLE_BUTTON, true);
				adapter->OnMouseMiddleButtonDownEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, false);				
				adapter->OnMouseRightButtonUpEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::RIGHT_BUTTON, true);
				adapter->OnMouseRightButtonDownEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, false);
				adapter->OnMouseLeftButtonUpEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;
				Mouse::Instance()->SetButtonState(Mouse::LEFT_BUTTON, true);
				adapter->OnMouseLeftButtonDownEvent(event);
			}
			break;
		case WM_MOUSEHOVER:
			{
				MouseHooverEvent* event = new MouseHooverEvent;
				event->x = LOWORD(lParam);
				event->y = GetHeight(hwnd) - HIWORD(lParam);
				event->x_prev = x_prev;
				event->y_prev = y_prev;
				adapter->OnMouseHooverEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;

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
				adapter->OnMouseMoveEvent(event);
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
				event->controlKey = (wParam & MK_CONTROL) == 0;
				event->leftButton = (wParam & MK_LBUTTON) == 0;
				event->middleButton = (wParam & MK_MBUTTON) == 0;
				event->rightButton = (wParam & MK_RBUTTON) == 0;
				event->shiftButton = (wParam & MK_SHIFT) == 0;
				event->xbutton1 = (wParam & MK_XBUTTON1) == 0;
				event->xbutton2 = (wParam & MK_XBUTTON2) == 0;				
				adapter->OnMouseWheelEvent(event);
			}
			break;
		case WM_CHAR:
			{
				KeyCharEvent* event = new KeyCharEvent;
				event->key = (int)wParam;
				event->repeat_count = (lParam & 0xFFFF) == 0;
				event->scan_code = (lParam & 0xFF0000) == 0;
				event->isExtended = (lParam & 0x1000000) == 0;
				event->isAltPressed = (lParam & 0x20000000) == 0;
				event->prevState = (lParam & 0x40000000) == 0;
				event->transitionState = (lParam & 0x80000000) == 0;
				adapter->OnCharEvent(event);
			}
			break;
		case WM_UNICHAR:
			{
				KeyWCharEvent* event = new KeyWCharEvent;
				event->key = (int)wParam;
				event->repeat_count = (lParam & 0xFFFF) == 0;
				event->scan_code = (lParam & 0xFF0000) == 0;
				event->isExtended = (lParam & 0x1000000) == 0;
				event->isAltPressed = (lParam & 0x20000000) == 0;
				event->prevState = (lParam & 0x40000000) == 0;
				event->transitionState = (lParam & 0x80000000) == 0;
				adapter->OnWideCharEvent(event);
			}
			break;
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			{
				KeyDownEvent* event = new KeyDownEvent;
				event->key = (int)wParam;
				event->repeat_count = (lParam & 0xFFFF) == 0;
				event->scan_code = (lParam & 0xFF0000) == 0;
				event->isExtended = (lParam & 0x1000000) == 0;
				event->prevState = (lParam & 0x40000000) == 0;
				event->transitionState = (lParam & 0x80000000) == 0;
				Keyboard::Instance()->SetKeyState(wParam, true);
				adapter->OnKeyDownEvent(event);
				break;
			}
		case WM_SYSKEYUP:
		case WM_KEYUP:
			{
				KeyUpEvent* event = new KeyUpEvent;
				event->key = (int)wParam;				
				Keyboard::Instance()->SetKeyState(wParam, false);
				adapter->OnKeyUpEvent(event);
				break;
			}
		case WM_SIZE:
			{
				WindowResizeEvent* event = new WindowResizeEvent;
				event->minimized = (wParam & SIZE_MINIMIZED) == 0;
				event->restored = (wParam & SIZE_RESTORED) == 0;
				event->width = LOWORD(lParam);
				event->height = HIWORD(lParam);
				adapter->OnResizeEvent(event);

				/*		RECT r;
				GetWindowRect(window->m_windowHandle, &r);
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
				adapter = reinterpret_cast<WindowAdapter*>(cs->lpCreateParams);
				adapter->OnCreateEvent();
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			adapter->OnDestroyEvent();
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	int Window::GetX() const
	{
		RECT wrect;
		GetClientRect(m_windowHandle, &wrect);

		return wrect.left;
	}

	int Window::GetY() const
	{
		RECT wrect;
		GetClientRect(m_windowHandle, &wrect);
		return wrect.top;
	}

	int Window::GetWidth() const
	{
		RECT rect;
		GetClientRect(m_windowHandle, &rect);
		return rect.right - rect.left;
	}

	int Window::GetHeight() const
	{
		RECT rect;;
		if (!GetClientRect(m_windowHandle, &rect))
			throw PunkInvalidArgumentException(L"Can't get window height");
		//GetWindowRect(m_windowHandle, &rect);
		return rect.bottom - rect.top;
	}
}

#endif  //_WIN32
