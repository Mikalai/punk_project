#ifndef _H_PUNK_SYSTEM_CONSURRENCY_INTERLOCKED
#define _H_PUNK_SYSTEM_CONSURRENCY_INTERLOCKED

#ifdef _WIN32
#include "win32/atomic_win32.h"
#endif

#ifdef __linux__
#include "linux/"
#endif

#endif	//	_H_PUNK_SYSTEM_CONSURRENCY_INTERLOCKED