#ifdef _WIN32

#include "timer_win32.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace System
{
	std::auto_ptr<Timer> Timer::m_instance;

    Timer::Timer()
    {
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		freq = li.QuadPart;
		QueryPerformanceCounter(&startPoint);
    }

    double Timer::GetElapsedTime() const
    {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return (double)(li.QuadPart - startPoint.QuadPart)/(double)freq;
    }

    void Timer::UpdateStartPoint()
    {
		QueryPerformanceCounter(&startPoint);
    }

	Timer* Timer::GetGlobalTimer()
	{
		if (!m_instance.get())
			m_instance.reset(new Timer());
		return m_instance.get();
	}

	void Timer::DestroyGlobalTimer()
	{
		m_instance.reset(0);
	}

	__int64 Timer::GetCurrentSystemTimeUS()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return li.QuadPart * 1000000 / freq;
	}
}

#endif  //_WIN32
