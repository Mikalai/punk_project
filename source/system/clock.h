/*
	File: Clock.h
	Author: Mikalaj Abramau
	Desc: Contains a class to access system time
*/

#ifndef _H_PUNK_CLOCK
#define _H_PUNK_CLOCK

#ifdef _WIN32
#include "win32/clock_win32.h"
#endif

#ifdef __linux__
#include "linux/clock_linux.h"
#endif

#endif	//_H_PUNK_CLOCK
