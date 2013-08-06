
#include "timer.h"
#include <stdint.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <sys/time.h>
#endif

namespace System
{
	struct Timer::Impl
	{
        double m_last_check;

        uint64_t GetTickCount() const
        {
#ifdef _WIN32
            LARGE_INTEGER li;
            QueryPerformanceCounter(&li);
            return li.QuadPart;
#elif defined __gnu_linux__
            union {
                unsigned long dw[2];
                unsigned long long counter;
            } tc;

            __asm__ __volatile__ (
                        ".byte 0x0f, 0x31\n"
                        :"d=" (tc.dw[1]), "a=" (tc.dw[0]):
                :"%eax", "%edx"
                );
            return tc.counter;
#endif
        }

        //  returns time in seconds
        double GetCurrentTime() const
        {
#ifdef _WIN32
            auto current = GetTickCount()/(double)GetFrequency();
            return current - m_last_check;
#elif defined __gnu_linux__
            timeval cur_time;
            gettimeofday(&cur_time, nullptr);
            double res = cur_time.tv_sec + (double)cur_time.tv_usec / 1000000.0;
            return res;
#endif
        }

        uint64_t GetFrequency() const
        {
#ifdef _WIN32
            LARGE_INTEGER li;
            QueryPerformanceFrequency(&li);
            return li.QuadPart;
#elif defined __gnu_linux__
            return 0;
#endif
        }

		double GetElapsedSeconds() const
		{
            double res = GetCurrentTime() - m_last_check;
            return res;
		}

		double GetElapsedMiliseconds() const
		{
			return GetElapsedSeconds() * 1000.0;
		}

        double Reset()
		{
            m_last_check = GetCurrentTime();
            return m_last_check;
		}

		Impl()
        {}

		Impl(const Impl& v)
            : m_last_check(v.m_last_check)
		{}
	};

    Timer::Timer()
		: impl(new Impl)
    {
    }

	Timer::~Timer()
	{
		delete impl;
		impl = nullptr;
	}

	double Timer::GetElapsedSeconds() const
    {
		return impl->GetElapsedSeconds();
    }

	double Timer::GetElapsedMiliseconds() const
	{
		return impl->GetElapsedMiliseconds();
	}
		
    double Timer::Reset()
    {
		return impl->Reset();
    }

    double Timer::GetCurrentTime() const
    {
        return impl->GetCurrentTime();
    }
}
