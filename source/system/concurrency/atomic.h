#ifndef _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED
#define _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED

#include <cstdint>

#ifdef _WIN32
#include <intrin.h>
#elif defined __gnu_linux__
#include <pthread.h>
#endif

namespace System
{
    inline long AtomicCompareExchange(volatile int32_t* value, int32_t exchange, int32_t compare)
	{
#ifdef _WIN32
		return _InterlockedCompareExchange((volatile long*)value, (long)exchange, (long)compare);
#elif defined __gnu_linux__
#endif

	}

    inline long AtomicIncrement32(volatile int32_t* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement((volatile long*)value);
#endif
	}

    inline short AtomicIncrement16(volatile int16_t* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement16(value);
#endif
	}

    inline long AtomicDecrement32(volatile int32_t* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement((volatile long*)value);
#endif
	}

    inline long AtomicDecrement16(volatile int16_t* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement16(value);
#endif
	}
}

#endif	//	_H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED
