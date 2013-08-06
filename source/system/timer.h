#ifndef _H_PUNK_SYSTEM_TIMER
#define _H_PUNK_SYSTEM_TIMER

#include <memory>
#include "../config.h"

namespace System
{
	/**
	*	Timer is used for strict time count
	*/
	class PUNK_ENGINE_API Timer final
    {
    public:
        Timer();
		~Timer();

        double GetCurrentTime() const;
        double GetElapsedSeconds() const;
		double GetElapsedMiliseconds() const;
        double Reset();

	private:
		Timer(const Timer&);
		Timer& operator = (const Timer&);

		struct Impl;
		Impl* impl;
    };
}

#endif  //  _H_PUNK_TIMER
