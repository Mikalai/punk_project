#ifndef _H_PUNK_ENVIRONMENT_WIN32
#define _H_PUNK_ENVIRONMENT_WIN32

#include "string_win32.h"
#include "../singletone.h"
#include "../config.h"

namespace System
{
	SingletoneInterface(Environment, LIB_SYSTEM);

	class LIB_SYSTEM Environment : public Singletone(Environment)
	{
	public:
		static string GetCurrentDirectory();
		static void SetCurrentDirectory(const string& dir);
	};
}

#endif