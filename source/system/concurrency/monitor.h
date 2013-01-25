#ifndef _H_PUNK_MONITOR
#define _H_PUNK_MONITOR

#ifdef _WIN32
#include "win32/monitor_win32.h"
#endif

#ifdef __linux__
#include "linux/monitor_linux.h"
#endif

#endif	//_H_PUNK_MONITOR
