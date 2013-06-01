#ifndef _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED
#define _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED

#ifdef _WIN32
#include <intrin.h>
#endif

#include "../types.h"

namespace System
{
	inline long AtomicCompareExchange(volatile Int32* value, Int32 exchange, Int32 compare)
	{
#ifdef _WIN32
		return _InterlockedCompareExchange((volatile long*)value, (long)exchange, (long)compare);
#endif
	}

	inline long AtomicIncrement32(volatile Int32* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement((volatile long*)value);
#endif
	}

	inline short AtomicIncrement16(volatile Int16* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement16(value);
#endif
	}

	inline long AtomicDecrement32(volatile Int32* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement((volatile long*)value);
#endif
	}

	inline long AtomicDecrement16(volatile Int16* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement16(value);
#endif
	}
}

#endif	//	_H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED