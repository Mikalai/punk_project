/*
        File: clock_linux.h
	Author: Mikalaj Abramau
        Desc: Contains a class to access system time in linux
*/

#ifndef _H_PUNK_LINUX_CLOCK
#define _H_PUNK_LINUX_CLOCK

namespace System
{
    class Clock
    {
        static const int timeSize = 64;
        char time[timeSize];
    public:
        const char* ToString() const;
        int Hour() const;
        int Minute() const;
        int Second() const;
    };
}

namespace CommonStaff
{
    extern ::Clock g_clock;
}

#endif	//_H_PUNK_LINUX_CLOCK
