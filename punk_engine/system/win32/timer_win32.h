/*
    File: timer.h
    Author: Nickolai Abramov
    Desc: High resolution timer
*/

#ifndef _H_PUNK_WIN32_TIMER
#define _H_PUNK_WIN32_TIMER

#include <time.h>
#include "types_win32.h"
#include <Windows.h>

namespace System
{
	class MODULE_SYSTEM Timer
    {
        __int64 freq;
		LARGE_INTEGER startPoint;
    public:
        Timer();
        __int64 GetElapsedTime() const;
        void UpdateStartPoint();
    };
}

#endif  //  _H_PUNK_TIMER
