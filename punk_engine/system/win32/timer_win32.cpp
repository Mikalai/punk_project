#ifdef _WIN32

#include "timer_win32.h"
#include <Windows.h>

namespace System
{
    Timer::Timer()
    {
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		freq = li.QuadPart;
		QueryPerformanceCounter(&startPoint);
    }

    __int64 Timer::GetElapsedTime() const
    {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return (double)(li.QuadPart - startPoint.QuadPart)*1000000/freq;
    }

    void Timer::UpdateStartPoint()
    {
		QueryPerformanceCounter(&startPoint);
    }
}

#endif  //_WIN32
