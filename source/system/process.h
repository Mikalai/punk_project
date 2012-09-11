#ifndef _H_PUNK_PROCESS
#define _H_PUNK_PROCESS

#ifdef _WIN32
#include "win32\process_win32.h"
#endif

#ifdef __linux__
#include "linux\process_linux.h"
#endif

#endif