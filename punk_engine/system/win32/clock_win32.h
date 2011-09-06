/*
        File: clock_win32.h
	Author: Nickolai Abramov
	Desc: Contains a class to access system time
*/

#ifndef _H_PUNK_WIN32_CLOCK
#define _H_PUNK_WIN32_CLOCK

#include "..\string.h"
#include "../singletone.h"
#include "../config.h"

namespace System
{
	SingletoneInterface(Clock, LIB_SYSTEM)

	class LIB_SYSTEM Clock : public Singletone(Clock)
    {
        static const int timeSize = 64;
        wchar_t the_time[timeSize];
    public:
        string ToString() const;
        int Hour() const;
        int Minute() const;
        int Second() const;
    };
}

#endif	//_H_PUNK_WIN32_CLOCK
