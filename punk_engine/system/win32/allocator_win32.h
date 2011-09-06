#ifndef _H_PUNK_ALLOCATOR_WIN32
#define _H_PUNK_ALLOCATOR_WIN32

#include <Windows.h>

namespace System
{
	class Allocator
	{
		static int totalSize;
		static int allocationCalled;
		static int destructionCalled;
		static HANDLE heap;
	public:

		static const int& GetTotalMemoryUsed();
		static const int& GetTotalAllocationCount();
		static const int& GetTotalDeallocationCount();
		static bool CheckMemoryLeaks();
		static void* Alloc(int size);
		static void Free(void* object);

	};

}

#endif