
#ifdef __linux__

#include "clock_linux.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

namespace CommonStaff
{
	::Clock g_clock;
}

namespace System
{
	const char* Clock::ToString() const
	{
		time_t t = ::time(NULL);
		tm* curTime = localtime(&t);
		sprintf((char*)time, "%d:%d:%d", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
		return time;
	}

	int Clock::Hour() const
	{
		time_t t = ::time(NULL);
		tm* curTime = localtime(&t);
		return curTime->tm_hour;
	}

	int Clock::Minute() const
	{
		time_t t = ::time(NULL);
		tm* curTime = localtime(&t);
		return curTime->tm_min;
	}

	int Clock::Second() const
	{
		time_t t = ::time(NULL);
		tm* curTime = localtime(&t);
		return curTime->tm_sec;
	}
}

#endif  //__linux__
