#ifndef _H_PUNK_MOUSE
#define _H_PUNK_MOUSE

#ifdef _WIN32
#include "win32/mouse_win32.h"
#endif

#ifdef __linux__
#include "linux/mouse_linux.h"
#endif

#endif