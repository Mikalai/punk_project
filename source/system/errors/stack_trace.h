#ifndef _H_PUNK_STACK_TRACE_WIN32
#define _H_PUNK_STACK_TRACE_WIN32

#include <iosfwd>

#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	class PUNK_ENGINE Stack
	{
	public:
		Stack();
		~Stack();
		string GetStackTrace();
		void Print(std::wostream& stream);
	};
}

#endif	//_H_PUNK_STACK_TRACE_WIN32