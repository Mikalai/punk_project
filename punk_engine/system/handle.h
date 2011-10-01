#ifndef H_HANDLER
#define H_HANDLER

#ifdef _WIN32
#include "win32\handle_win32.h"
#endif

#ifdef __linux__
#include "linux\handler_linux.h"
#endif

#endif