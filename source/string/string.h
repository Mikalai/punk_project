#ifndef _H_PUNK_STRING
#define _H_PUNK_STRING


#ifdef USE_STATIC_STRING
#include "win32\static_string.h"
#else
#ifdef _WIN32
#include "win32\string_win32.h"
#endif
#endif

#ifdef __linux__
#include "linux\"
#endif

#endif