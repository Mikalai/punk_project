#include <time.h>
#include "system_clock.h"

namespace System
{
	//
	//	system clock gose here
	//
	std::auto_ptr<SystemClock> SystemClock::m_instance;

	SystemClock::SystemClock()
	{
	}

	SystemClock* SystemClock::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new SystemClock());
		return m_instance.get();
	}

	void SystemClock::Destroy()
	{
		m_instance.reset(0);
	}

	__int64 SystemClock::GetUTCTimeInSecondsSinceMidnightJanuary_1_1970()
	{
		time_t t;
		time(&t);
		return t;
	}

	const string SystemClock::NowAsUTC()
	{
		char buffer[32];
		time_t t;
		time(&t);
		tm _tm;
		_gmtime64_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
		// replace new line in the time string. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
		return string(buffer);
	}

	const string SystemClock::NowAsLocal()
	{
		char buffer[32];
		time_t t;
		time(&t);
		tm _tm;
		_localtime64_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
		// replace new line in the time string. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
		return string(buffer);
	}
}