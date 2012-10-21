/*
        File: clock_win32.h
	Author: Mikalaj Abramau
	Desc: Contains a class to access system time
*/

#ifndef _H_PUNK_WIN32_CLOCK
#define _H_PUNK_WIN32_CLOCK

#include <time.h>
#include "../../string/string.h"
#include "../singletone.h"
#include "../../config.h"
#include "buffer_win32.h"

namespace System
{
	class PUNK_ENGINE Clock
    {
		SingletoneInterface(Clock);

	private:
        static const int timeSize = 64;
        wchar_t the_time[timeSize];
		__int64 m_time;
		__int64 m_us;
		tm m_date;

    public:
		Clock();

		__int64 Now();
		void Advance(__int64 us);

        const string ToString() const;
		int Year() const;
		int Month() const;
		int MonthDay() const;
		int WeekDay() const;
		int YearDay() const;
        int Hour() const;
        int Minute() const;
        int Second() const;
		int MilliSecond() const;

		void Set(int Year, int Month, int Day, int Hour, int Min, int Sec);

		void Store(Buffer& buffer);
		void Restore(Buffer& buffer);
    };
}

#endif	//_H_PUNK_WIN32_CLOCK
