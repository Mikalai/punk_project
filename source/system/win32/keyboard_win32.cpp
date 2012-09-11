#include "keyboard_win32.h"
#include <memory.h>

namespace System
{
	SingletoneImplementation(Keyboard);

	Keyboard::Keyboard() 
	{
		memset(m_keys, 0, sizeof(m_keys));
	}

	bool& Keyboard::operator[] (int key)
	{
		return m_keys[key];
	}

	const bool& Keyboard::operator[] (int key) const
	{
		return m_keys[key];
	}

	void Keyboard::SetKeyState(int key, bool state)
	{
		m_keys[key] = state;
	}

	bool Keyboard::GetKeyState(int key) const
	{
		return m_keys[key];
	}
}
