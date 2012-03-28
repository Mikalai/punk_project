#ifndef _H_PUNK_KEYBOARD_WIN32
#define _H_PUNK_KEYBOARD_WIN32

#include "../singletone.h"
#include "../config.h"

namespace System
{
	SingletoneInterface(Keyboard, MODULE_SYSTEM);

	class MODULE_SYSTEM Keyboard : public Singletone(Keyboard)
	{
		bool m_keys[256];
		
	public:

		Keyboard();

		const bool& operator[] (int key) const;
		bool& operator[] (int key);

		void SetKeyState(int key, bool state);
		bool GetKeyState(int key) const;
	};
}

#endif