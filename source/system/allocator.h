#ifndef _H_PUNK_SYSTEM_ALLOCATOR
#define _H_PUNK_SYSTEM_ALLOCATOR

#include <new>

namespace System
{
	template<class T>
	class DefaultAllocator
	{
	public:

		static void* Alloc(int size)
		{
			return operator new (size);
		}

		static void Free(void* v)
		{
			operator delete (v);
		}

		static T* Alloc()
		{
			return new T();
		}

		static void Free(T* v)
		{
			delete v;
		}

		static T* AllocArray(int count)
		{
			return new T[count];
		}

		static T* FreeArray(T* v)
		{
			delete[] v;
		}
	};
};

#endif //	_H_PUNK_SYSTEM_ALLOCATOR