#ifndef _H_PUNK_SYSTEM_SEMAPHORE
#define _H_PUNK_SYSTEM_SEMAPHORE

#ifdef _WIN32
#include "win32/semaphore_win32.h"
#endif

#ifdef __linux__
#include "linuxr/semaphore_linux.h"
#endif

#endif	//	_H_PUNK_SYSTEM_SEMAPHORE