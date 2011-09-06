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
    class Timer
    {
        double period;
		LARGE_INTEGER startPoint;
    public:
        Timer();
        double GetElapsedTime() const;
        void UpdateStartPoint();
    };
}

#endif  //  _H_PUNK_TIMER
