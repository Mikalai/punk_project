#ifdef _WIN32

#include "timer_win32.h"
#include <Windows.h>

namespace System
{
    Timer::Timer()
    {
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		period = 1.0/(double)li.QuadPart;
		QueryPerformanceCounter(&startPoint);
    }

    double Timer::GetElapsedTime() const
    {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return (double)(li.QuadPart - startPoint.QuadPart)*period;
    }

    void Timer::UpdateStartPoint()
    {
		QueryPerformanceCounter(&startPoint);
    }
}

#endif  //_WIN32
