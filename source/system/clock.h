#ifndef _H_PUNK_SYSTEM_CLOCK
#define _H_PUNK_SYSTEM_CLOCK

#include <time.h>
#include "../config.h"
#include "../string/string.h"
#include "buffer.h"
#include "types.h"

namespace System
{
	class PUNK_ENGINE Clock
    {	
    public:
		Clock();

		/**
		*	Used to retrieve current virtual time value
		*	\returns Current virtual time
		*/
		Int64 Now();
		
		/**
		*	Used to increment time of the clock
		*	\param us Time in microseconds
		*/
		void Advance(Int64 us);

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

		static Clock* Instance();
		static void Destroy();

		static Int64 SysTimeAsSecondsFromJanuary_1970_1();
		static const string SysTimeAsUTC();
		static const string SysTimeNowAsLocal();

	private:
		static Clock* m_instance;

        static const int timeSize = 64;
        wchar_t the_time[timeSize];
		Int64 m_time;
		Int64 m_us;
		tm m_date;
    };
}

#endif	//_H_PUNK_SYSTEM_CLOCK
