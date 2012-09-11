#ifndef _H_PUNK_THREAD
#define _H_PUNK_THREAD

#ifdef _WIN32
#include "win32\thread_win32.h"
#endif

#ifdef __linux__
#include "linux\thread_linux.h"
#endif

#endif