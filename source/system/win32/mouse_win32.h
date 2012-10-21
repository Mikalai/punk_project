#ifndef _H_PUNK_MOUSE_WIN32
#define _H_PUNK_MOUSE_WIN32

#include "../../config.h"
#include "../singletone.h"
#include "window_win32.h"

namespace System
{
	class PUNK_ENGINE Mouse
	{
		SingletoneInterface(Mouse);

	public:
		enum MouseButtons { LEFT_BUTTON, RIGHT_BUTTON, MIDDLE_BUTTON };

	private:
		
		static const int MAX_MOUSE_BUTTONS = 3;
		bool m_buttons[MAX_MOUSE_BUTTONS];
		bool m_locked;
		bool m_visible;
		const Window* m_region;

	public:

		Mouse();
		void Show(bool value);
		void LockInWindow(bool value);
		void SetButtonState(MouseButtons button, bool state);
		bool GetButtonState(MouseButtons button) const;
		void BindCursorToWindow(const Window* window);

		int GetGlobalX() const;
		int GetGlobalY() const;
		int GetLocalX() const;
		int GetLocalY() const;
		
		bool IsLocked() const;
		bool IsVisible() const;
		const Window* GetBoundedWindow() const;
	};
}

#endif