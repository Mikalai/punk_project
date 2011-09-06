#ifndef _H_PUNK_SOFT_DRIVER
#define _H_PUNK_SOFT_DRIVER

#ifdef _WIN32
#include "win32/driver_win32.h"
#endif

#ifdef __linux__
#include "linux/driver_linux.h"
#endif

#endif