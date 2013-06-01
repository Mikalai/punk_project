#ifndef _H_PUNK_WINDOW_ADAPTER
#define _H_PUNK_WINDOW_ADAPTER

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#endif

#include "../types.h"

namespace System
{
	class WindowResizeEvent;
	class KeyUpEvent;
	class KeyDownEvent;
	class KeyWCharEvent;
	class KeyCharEvent;
	class MouseWheelEvent;
	class MouseMoveEvent;
	class MouseHooverEvent;
	class MouseLeftButtonDownEvent;
	class MouseLeftButtonUpEvent;
	class MouseRightButtonDownEvent;
	class MouseRightButtonUpEvent;
	class MouseMiddleButtonDownEvent;
	class MouseMiddleButtonUpEvent;
	class IdleEvent;

	struct WindowDesc
	{
		unsigned m_x;
		unsigned m_y;
		unsigned m_width;
		unsigned m_height;

#ifdef _WIN32
        bool m_use_parent_window;
        HWND m_hwnd;
#endif
        WindowDesc() : m_x(100), m_y(100), m_width(1024), m_height(768), m_use_parent_window(false), m_hwnd(0) {}
	};

	class WindowAdapter
	{
	public:
		virtual void WndOnIdleEvent(IdleEvent* event) = 0;
		virtual void WndOnMouseMiddleButtonUpEvent(MouseMiddleButtonUpEvent* event) = 0;
		virtual void WndOnMouseMiddleButtonDownEvent(MouseMiddleButtonDownEvent* event) = 0;
		virtual void WndOnMouseRightButtonUpEvent(MouseRightButtonUpEvent* event) = 0;
		virtual void WndOnMouseRightButtonDownEvent(MouseRightButtonDownEvent* event) = 0;
		virtual void WndOnMouseLeftButtonUpEvent(MouseLeftButtonUpEvent* event) = 0;
		virtual void WndOnMouseLeftButtonDownEvent(MouseLeftButtonDownEvent* event) = 0;
		virtual void WndOnMouseHooverEvent(MouseHooverEvent* event) = 0;
		virtual void WndOnMouseMoveEvent(MouseMoveEvent* event) = 0;
		virtual void WndOnMouseWheelEvent(MouseWheelEvent* event) = 0;
		virtual void WndOnCharEvent(KeyCharEvent* value) = 0;
		virtual void WndOnWideCharEvent(KeyWCharEvent* event) = 0;
		virtual void WndOnKeyDownEvent(KeyDownEvent* event) = 0;
		virtual void WndOnKeyUpEvent(KeyUpEvent* event) = 0;
		virtual void WndOnResizeEvent(WindowResizeEvent* event) = 0;
		virtual void WndOnCreateEvent() = 0;
		virtual void WndOnDestroyEvent() = 0;
#ifdef _WIN32
        virtual LRESULT CustomDefWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
#endif
	};
}

#endif	//	_H_PUNK_WINDOW_ADAPTER
