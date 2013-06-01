
#include "timer.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

namespace System
{
	struct Timer::Impl
	{
#ifdef _WIN32		
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_last_check;
#endif

		double GetElapsedSeconds() const
		{
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			return (double)(li.QuadPart - m_last_check.QuadPart)/(double)m_frequency.QuadPart;
		}

		double GetElapsedMiliseconds() const
		{
			return GetElapsedSeconds() * 1000.0;
		}

		long long GetElapsedTicks() const
		{
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			return li.QuadPart - m_last_check.QuadPart;
		}

		long long GetFrequency() const
		{
			return m_frequency.QuadPart;
		}

		long long Reset()
		{
			QueryPerformanceCounter(&m_last_check);
			return m_last_check.QuadPart;
		}

		Impl()
		{
			LARGE_INTEGER li;
			QueryPerformanceFrequency(&li);
			m_frequency = li;
			QueryPerformanceCounter(&m_last_check);
		}

		Impl(const Impl& v)
			: m_frequency(v.m_frequency)
			, m_last_check(v.m_last_check)
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
		
	long long Timer::GetElapsedTicks() const
	{
		return impl->GetElapsedTicks();
	}

	long long Timer::GetFrequency() const
	{
		return impl->GetFrequency();
	}

	long long Timer::Reset()
    {
		return impl->Reset();
    }
}
