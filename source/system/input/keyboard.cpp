#include "keyboard.h"
#include <memory.h>

namespace System
{
	Keyboard* Keyboard::m_instance;

	Keyboard* Keyboard::Instance()
	{
		if (!m_instance)
			m_instance = new Keyboard;
		return m_instance;
	}

	void Keyboard::Destroy()
	{
		delete m_instance;
        m_instance = 0;
	}

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
