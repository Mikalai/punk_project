#ifdef __linux__

#include "timer_linux.h"

namespace System
{
    Timer::Timer()
    {
        gettimeofday(&lastTime, 0);
    }

    Int64 Timer::GetElapsedTime() const
    {
        timeval value;
        gettimeofday(&value,0);
        return value.tv_usec + value.tv_sec * 1000000;
    }

    void Timer::UpdateStartPoint()
    {
        gettimeofday(&lastTime, 0);
    }
}

#endif  //__linux__
