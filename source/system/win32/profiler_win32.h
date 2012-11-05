#ifndef _H_PUNK_SYSTE_PROFILER_WIN32
#define _H_PUNK_SYSTE_PROFILER_WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	/*
	*	Used to measure small pieces of time
	*/
	class PUNK_ENGINE Profiler
	{
		//	Frequency of the CPU
		LARGE_INTEGER m_frequency;
		//	Start counter value
		LARGE_INTEGER m_start;
		//	End counter value
		LARGE_INTEGER m_end;
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
		__int64 End();
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

#endif