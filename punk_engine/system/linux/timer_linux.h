/*
    File: timer.h
    Author: Nickolai Abramov
    Desc: High resolution timer
*/

#ifndef _H_PUNK_LINUX_TIMER
#define _H_PUNK_LINUX_TIMER

#include <sys/time.h>
#include "types_linux.h"

namespace System
{
    class Timer
    {
        timeval lastTime;
    public:
        Timer();
        Int64 GetElapsedTime() const;
        void UpdateStartPoint();
    };
}

#endif  //  _H_PUNK_TIMER
