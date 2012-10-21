/*
    File: timer.h
    Author: Mikalaj Abramau
    Desc: High resolution timer
*/

#ifndef _H_PUNK_TIMER
#define _H_PUNK_TIMER

#ifdef _WIN32
#include "win32/timer_win32.h"
#endif

#ifdef __linux__
#include "linux/timer_linux.h"
#endif

#endif  //  _H_PUNK_TIMER
