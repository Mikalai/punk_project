#ifndef _H_PUNK_SOFT_VIDEO_BUFFER
#define _H_PUNK_SOFT_VIDEO_BUFFER

#ifdef _WIN32
#include "win32/buffer_win32.h"
#endif

#ifdef __linux__
#include "linux/buffer_linux.h"
#endif

#endif