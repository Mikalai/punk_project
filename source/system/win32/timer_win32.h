/*
    File: timer.h
    Author: Nickolai Abramov
    Desc: High resolution timer
*/

#ifndef _H_PUNK_WIN32_TIMER
#define _H_PUNK_WIN32_TIMER

#include <time.h>
#include "types_win32.h"

#include <Windows.h>

namespace System
{
	class PUNK_ENGINE Timer
    {
		static std::auto_ptr<Timer> m_instance;

        __int64 freq;
		LARGE_INTEGER startPoint;

    public:
        Timer();
        double GetElapsedTime() const;
        void UpdateStartPoint();

		__int64 GetCurrentSystemTimeUS();

		static Timer* GetGlobalTimer();
		static void DestroyGlobalTimer();
    };
}

#endif  //  _H_PUNK_TIMER
