#ifndef _H_PUNK_SYSTEM_CLOCK
#define _H_PUNK_SYSTEM_CLOCK

#include <memory>

#include "../config.h"
#include "../string/string.h"

namespace System
{
	/*
	/*	System clock goes here
	*/
	class PUNK_ENGINE SystemClock
	{
		static std::auto_ptr<SystemClock> m_instance;
		SystemClock();
		SystemClock(const SystemClock&);
		SystemClock& operator = (const SystemClock&);

	public:

		__int64 GetUTCTimeInSecondsSinceMidnightJanuary_1_1970();
		const string NowAsUTC();
		const string NowAsLocal();

		static SystemClock* Instance();
		static void Destroy();
	};
}

#endif	//	_H_PUNK_SYSTEM_CLOCK