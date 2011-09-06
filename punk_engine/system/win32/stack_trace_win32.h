#ifndef _H_PUNK_STACK_TRACE_WIN32
#define _H_PUNK_STACK_TRACE_WIN32

#include "../config.h"
#include "string_win32.h"

namespace System
{
	class LIB_SYSTEM Stack
	{
	public:
		Stack();
		~Stack();
		string GetStackTrace();
	};
}

#endif	//_H_PUNK_STACK_TRACE_WIN32