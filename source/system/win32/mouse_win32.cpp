#include "mouse_win32.h"

namespace System
{
	SingletoneImplementation(Mouse);

	Mouse::Mouse() : m_region(0)
	{
		memset(m_buttons, 0, sizeof(m_buttons));
	}

	void Mouse::SetButtonState(Mouse::MouseButtons button, bool state)
	{
		m_buttons[button] = state;
	}

	bool Mouse::GetButtonState(System::Mouse::MouseButtons button) const
	{
		return m_buttons[button];
	}

	void Mouse::BindCursorToWindow(const Window* window)
	{
		m_region = window;
	}

	void Mouse::LockInWindow(bool value)
	{
		m_locked = value;
	}

	void Mouse::Show(bool value)
	{
		ShowCursor(m_visible = value);
	}

	bool Mouse::IsLocked() const
	{
		return m_locked;
	}

	bool Mouse::IsVisible() const
	{
		return m_visible;
	}

	const Window* Mouse::GetBoundedWindow() const
	{
		return m_region;
	}

	int Mouse::GetGlobalX() const
	{
		POINT p;
		GetCursorPos(&p);
		return p.x;
	}

	int Mouse::GetGlobalY() const
	{
		POINT p;
		GetCursorPos(&p);
		return p.y;
	}

	int Mouse::GetLocalX() const
	{
		POINT p;
		GetCursorPos(&p);
		if (m_region == 0)
			return p.x;
		return p.x - m_region->GetX();
	}

	int Mouse::GetLocalY() const
	{
		POINT p;
		GetCursorPos(&p);
		if (m_region == 0)
			return p.y;
		return p.y - m_region->GetY();
	}
}
