#ifndef _H_PUNK_SYSTEM_THREAD_MUTEX
#define _H_PUNK_SYSTEM_THREAD_MUTEX

#ifdef _WIN32
#include "win32/thread_mutex_win32.h"
#endif //	_WIN32

#ifdef __linux__
#include "linux/thread_mutex_linux.h"
#endif //	__linux__

#endif	//	_H_PUNK_SYSTEM_THREAD_MUTEX