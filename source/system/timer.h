#ifndef _H_PUNK_SYSTEM_TIMER
#define _H_PUNK_SYSTEM_TIMER

#include <memory>
#include "../config.h"

namespace System
{
	/**
	*	Timer is used for strict time count
	*/
	class PUNK_ENGINE Timer final
    {
    public:
        Timer();
		~Timer();

        double GetElapsedSeconds() const;
		double GetElapsedMiliseconds() const;
		long long GetElapsedTicks() const;
		long long GetFrequency() const;
        long long Reset();		

	private:
		Timer(const Timer&);
		Timer& operator = (const Timer&);

		struct Impl;
		Impl* impl;
    };
}

#endif  //  _H_PUNK_TIMER
