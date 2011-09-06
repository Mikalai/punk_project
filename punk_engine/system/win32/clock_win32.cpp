
#ifdef _WIN32

#include "clock_win32.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

namespace System
{
	SingletoneImplementation(Clock)

	string Clock::ToString() const
	{
		time_t t = ::time(NULL);
		tm curTime;
		localtime_s(&curTime, &t);
		return string::Format(L"%d:%d:%d", curTime.tm_hour, curTime.tm_min, curTime.tm_sec);
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

#endif
