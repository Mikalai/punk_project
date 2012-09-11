#ifndef _H_PUNK_KEYBOARD
#define _H_PUNK_KEYBOARD

#ifdef _WIN32
#include "win32\keyboard_win32.h"
#endif

#ifdef __linux
#include "linux\keyboard_linux.h"
#endif

#endif