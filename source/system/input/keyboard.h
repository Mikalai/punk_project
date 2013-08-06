#ifndef _H_PUNK_KEYBOARD_WIN32
#define _H_PUNK_KEYBOARD_WIN32

#include "../../config.h"

namespace System
{
	class PUNK_ENGINE_API Keyboard
	{	
	public:

		Keyboard();

		const bool& operator[] (int key) const;
		bool& operator[] (int key);

		void SetKeyState(int key, bool state);
		bool GetKeyState(int key) const;

		static Keyboard* Instance();
		static void Destroy();
	private:
		static Keyboard* m_instance;
		bool m_keys[256];		
	};
}

#endif