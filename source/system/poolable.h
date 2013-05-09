#ifndef _H_PUNK_SYSTEM_POOLABLE
#define _H_PUNK_SYSTEM_POOLABLE

#include "pool.h"
#include <new>

namespace System
{
	template<class T>
	class Poolable
	{
		static Pool<T> pool;	
	public:
        static void* operator new (size_t) { return (void*)pool.Alloc(); }
        static void operator delete (void* obj) { pool.Free((T*)obj); }
		static void ClearPool() { pool.Clear(); }
	};

	template<class T> Pool<T> Poolable<T>::pool;
}

#endif	//	_H_PUNK_SYSTEM_POOLABLE
