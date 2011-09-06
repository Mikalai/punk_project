#include "../exception.h"
#include "allocator_win32.h"
#include "../../common/logger.h"
namespace System
{
	const int maxHeapSize = 64*1024*1024;
	int Allocator::totalSize = 0;
	int Allocator::allocationCalled = 0;
	int Allocator::destructionCalled = 0;
	HANDLE Allocator::heap = 0;

	void* Allocator::Alloc(int size)
	{
		if (heap == 0)
		{
			heap = HeapCreate(0, maxHeapSize, 0);
			if (heap == 0)
				throw System::Exception(L"Can't create heap, not enough memory" + LOG_LOCATION_STRING);
		}

		void* res = HeapAlloc(heap, HEAP_ZERO_MEMORY, size);

		if (res == 0)
		{
			int freeSize = HeapCompact(heap, 0);
			if (freeSize < size)
			{
				throw System::Exception(System::string::Format(L"Can't allocate memory in heap. Needs %d bytes; available %d bytes (%s)",
					freeSize, size, LOG_LOCATION_STRING.Data()));
			}
			else
			{
				res = HeapAlloc(heap, HEAP_ZERO_MEMORY, size);
				if (res == 0)
					throw System::Exception(L"Can't allocate memory in heap" + LOG_LOCATION_STRING);
			}
		}

		totalSize += HeapSize(heap, 0, res);
		allocationCalled++;

		return res;
	}

	void Allocator::Free(void* object)
	{
		if (object == 0)
			return;

		int size = HeapSize(heap, 0, object);
		if (HeapFree(heap, 0, object))
		{
			destructionCalled++;
			totalSize -= size;

			if (totalSize == 0)
			{
				if (HeapDestroy(heap))
				{
					heap = 0;
				}
				else
				{
					throw System::Exception(L"Can't destroy heap" + LOG_LOCATION_STRING);
				}
			}
		}
		else
		{
			throw System::Exception(L"Can't frees memory" + LOG_LOCATION_STRING);
		}
	}

	bool Allocator::CheckMemoryLeaks()
	{
		if (totalSize != 0)
			throw System::Exception(L"Memory leak occured" + LOG_LOCATION_STRING);
		return false;
	}

	const int& Allocator::GetTotalAllocationCount()
	{
		return allocationCalled;
	}

	const int& Allocator::GetTotalDeallocationCount()
	{
		return destructionCalled;
	}

	const int& Allocator::GetTotalMemoryUsed()
	{
		return totalSize;
	}
}