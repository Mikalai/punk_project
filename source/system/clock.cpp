#include "clock.h"

#ifdef __GNUC__
#include <time.h>
#endif

#include <stdio.h>
#include <string.h>

namespace System
{
	Clock* Clock::m_instance;

	Clock* Clock::Instance()
	{
		if (!m_instance)
			m_instance = new Clock;
		return m_instance;
	}

	void Clock::Destroy()
	{
		delete m_instance;
		m_instance = 0;
	}

	Clock::Clock()
	{
		m_time = 0;
		m_us = 0;
		_localtime64_s(&m_date, &m_time);
	}

	const string Clock::ToString() const
	{
		wchar_t buffer[256];
		_wasctime_s(buffer, 256, &m_date);
		buffer[24] = 0;
		return string(buffer);
	}

	int Clock::Hour() const
	{
		return m_date.tm_hour;
	}

	int Clock::Minute() const
	{
		return m_date.tm_min;
	}

	int Clock::Second() const
	{
		return m_date.tm_sec;
	}

	int Clock::MonthDay() const
	{
		return m_date.tm_mday;
	}

	int Clock::Year() const
	{
		return m_date.tm_year;
	}

	int Clock::WeekDay() const
	{
		return m_date.tm_wday;
	}

	int Clock::YearDay() const
	{
		return m_date.tm_yday;
	}

	int Clock::MilliSecond() const
	{
		return (int)m_us;
	}

	int64_t Clock::Now()
	{
		return m_time;
	}

	void Clock::Advance(int64_t dt)
	{
		m_us += dt;
		m_time += m_us / 1000000;
		m_us %= 1000000;
		_gmtime64_s(&m_date, &m_time);
	}

	int64_t Clock::SysTimeAsSecondsFromJanuary_1970_1()
	{
		time_t t;
		time(&t);
		return t;
	}

	const string Clock::SysTimeAsUTC()
	{
		char buffer[32];
		__time32_t t;
		time(&t);
		tm _tm;
		_gmtime32_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
		// replace new line in the time string. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
		return string(buffer);
	}

	const string Clock::SysTimeNowAsLocal()
	{
		char buffer[32];
		time_t t;
		time(&t);
		tm _tm;
		_localtime32_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
		// replace new line in the time string. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
		return string(buffer);
	}

	void Clock::Set(int Year, int Month, int Day, int Hour, int Min, int Sec)
	{
		memset(&m_date, 0, sizeof(m_date));
		m_date.tm_year = Year;
		m_date.tm_mon = Month;
		m_date.tm_mday = Day;
		m_date.tm_hour = Hour;
		m_date.tm_min = Min;
		m_date.tm_sec = Sec;

		m_time = _mktime64(&m_date);
		_gmtime64_s(&m_date, &m_time);
	}
/*
	void Clock::Store(Buffer& buffer)
	{
		buffer.WriteSigned64(m_time);
		buffer.WriteSigned64(m_us);
	}

	void Clock::Restore(Buffer& buffer)
	{
		m_time = buffer.ReadSigned64();
		m_us = buffer.ReadSigned64();
		_gmtime64_s(&m_date, &m_time);
	}*/
}
