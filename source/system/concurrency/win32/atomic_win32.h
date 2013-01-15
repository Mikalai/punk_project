#ifndef _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED_WIN32
#define _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED_WIN32

#include <intrin.h>
#include "../../types/base_types.h"

namespace System
{

	inline long AtomicIncrement32(volatile int32* value)
	{
		return _InterlockedIncrement((volatile long*)value);
	}

	inline short AtomicIncrement16(volatile int16* value)
	{
		return _InterlockedIncrement16(value);
	}

	inline long AtomicDecrement32(volatile int32* value)
	{
		return _InterlockedDecrement((volatile long*)value);
	}

	inline long AtomicDecrement16(volatile int16* value)
	{
		return _InterlockedDecrement16(value);
	}
}

#endif	//	_H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED_WIN32