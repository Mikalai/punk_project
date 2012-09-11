#ifndef _H_SYSTEM_TYPES
#define _H_SYSTEM_TYPES

#ifdef _WIN32
#include "win32/types_win32.h"
#endif

#ifdef __linux__
#include "linux/types_linux.h"
#endif

#endif // _H_SYSTEM_TYPES
