#ifndef _H_PUNK_WINDOW_ADAPTER
#define _H_PUNK_WINDOW_ADAPTER

#include "../types/base_types.h"

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
		WindowDesc() : m_x(100), m_y(100), m_width(1024), m_height(768) {}
	};

	class WindowAdapter
	{
	public:
		virtual void OnIdleEvent(IdleEvent* event) = 0;
		virtual void OnMouseMiddleButtonUpEvent(MouseMiddleButtonUpEvent* event) = 0;
		virtual void OnMouseMiddleButtonDownEvent(MouseMiddleButtonDownEvent* event) = 0;
		virtual void OnMouseRightButtonUpEvent(MouseRightButtonUpEvent* event) = 0;
		virtual void OnMouseRightButtonDownEvent(MouseRightButtonDownEvent* event) = 0;
		virtual void OnMouseLeftButtonUpEvent(MouseLeftButtonUpEvent* event) = 0;
		virtual void OnMouseLeftButtonDownEvent(MouseLeftButtonDownEvent* event) = 0;
		virtual void OnMouseHooverEvent(MouseHooverEvent* event) = 0;
		virtual void OnMouseMoveEvent(MouseMoveEvent* event) = 0;
		virtual void OnMouseWheelEvent(MouseWheelEvent* event) = 0;
		virtual void OnCharEvent(KeyCharEvent* value) = 0;
		virtual void OnWideCharEvent(KeyWCharEvent* event) = 0;
		virtual void OnKeyDownEvent(KeyDownEvent* event) = 0;
		virtual void OnKeyUpEvent(KeyUpEvent* event) = 0;
		virtual void OnResizeEvent(WindowResizeEvent* event) = 0;
		virtual void OnCreateEvent() = 0;
		virtual void OnDestroyEvent() = 0;
	};
}

#endif	//	_H_PUNK_WINDOW_ADAPTER