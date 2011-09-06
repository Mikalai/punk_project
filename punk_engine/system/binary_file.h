#ifndef _H_PUNK_BINARY_FILE
#define _H_PUNK_BINARY_FILE

#ifdef _WIN32
#include "win32\binary_file_win32.h"
#endif

#ifdef __linux__
#include "linux\binary_file_linux.h"
#endif

#endif