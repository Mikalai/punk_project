#ifndef _H_PUNK_ENVIRONMENT
#define _H_PUNK_ENVIRONMENT

#ifdef _WIN32
#include "win32\environment_win32.h"
#endif

#ifdef __linux__
#include "linux\environment_linux.h"
#endif

#endif