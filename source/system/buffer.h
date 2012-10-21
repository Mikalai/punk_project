/*
	File: File.h
	Author: Mikalaj Abramau
	Desc: A simple text file
*/

#ifndef _H_PUNK_BUFFER
#define _H_PUNK_BUFFER

#ifdef _WIN32
#include "win32/buffer_win32.h"
#endif

#ifdef __linux__
#include "linux/"
#endif

#endif
