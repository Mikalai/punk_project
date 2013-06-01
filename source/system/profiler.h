#ifndef _H_PUNK_SYSTE_PROFILER
#define _H_PUNK_SYSTE_PROFILER

#include "../config.h"
#include "../string/string.h"
#include "timer.h"

namespace System
{
	/*
	*	Used to measure small pieces of time
	*/
	class PUNK_ENGINE_PUBLIC Profiler
	{
		//	High definition timer
		Timer m_timer;		
		// Text descritpion of current profiler
		string m_description;
		// No copy
		Profiler(const Profiler&);
		// No copy
		Profiler& operator = (const Profiler&);
	public:
		Profiler();
		/*
		*	Start profiler and assigns new description to it
		*	@param description Textual representation of the profiler
		*/
		void Start(const string& description);
		/*
		*	Stops profiling
		*	@returns Tick count elapsed from start
		*/
		long long End();
		/*
		*	Converts ticks to milliseconds
		*	@return Elapsed time ib milliseconds
		*/
		double ToMiliseconds() const;
		/*
		*	Returns nice textual representation of the profiling result
		*/
		const string ToString() const;
	};
}

#endif	//	_H_PUNK_SYSTE_PROFILER