#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include "config.h"
#include "dynamic_array.h"

namespace System
{
	template<class T>
	class Pool
	{
		DynamicArray<T*> m_items;
	public:

		T* Get()
		{
			return m_items.Pop();
		}

		void Put(T* e)
		{
			m_items.Push(e);
		}

	};
}

#endif