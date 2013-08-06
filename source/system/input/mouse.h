#ifndef _H_PUNK_SYSTEM_MOUSE
#define _H_PUNK_SYSTEM_MOUSE

#include "../../config.h"
#include "../smart_pointers/module.h"

namespace System
{
	class Window;

	class PUNK_ENGINE_API Mouse
	{
	public:
		enum MouseButtons { LEFT_BUTTON, RIGHT_BUTTON, MIDDLE_BUTTON };

	private:
		
		static const int MAX_MOUSE_BUTTONS = 3;
		bool m_buttons[MAX_MOUSE_BUTTONS];
		bool m_locked;
		bool m_visible;
		Window* m_region;

	public:

		Mouse();
		void Show(bool value);
		void LockInWindow(bool value);
		void SetButtonState(MouseButtons button, bool state);
		bool GetButtonState(MouseButtons button) const;
		void BindCursorToWindow(Window* window);

		int GetGlobalX() const;
		int GetGlobalY() const;
		int GetLocalX() const;
		int GetLocalY() const;
		
		bool IsLocked() const;
		bool IsVisible() const;
		Window* GetBoundedWindow() const;

		static Mouse* Instance();
		static void Destroy();
    private:
		static Mouse* m_instance;

	};
}

#endif