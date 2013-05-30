#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include <iostream>
#include <string.h>
#include "../config.h"
#include <deque>
#include "pool_manager.h"

namespace System
{
	template<class T>
	class Pool
	{
        std::deque<T*> m_free;
	public:

		Pool()
		{
			//out_message() << "Create pool for " << typeid(T).name() << ", and register cleaner in pool manager" << std::endl;
//			PoolManager::Instance()->AddCleaner(Poolable<T>::ClearPool);
		}

		~Pool()
		{
			Clear();
		}

        T* Alloc()
		{
			if (m_free.empty())
			{
//				out_message() << "Allocation requested for " << typeid(T).name() << std::endl;
                T* chunk = (T*)operator new(sizeof(T));
				//	clear memory
				::memset(chunk, 0, sizeof(T));
				return chunk;
			}
            T* chunk = m_free.front();
			//	clear memory
			memset(chunk, 0, sizeof(T));
			m_free.pop_front();
			return chunk;
		}

        void Free(T* value)
		{
			//out_message() << "Free requested" << std::endl;
			m_free.push_back(value);
		}

		void Clear()
		{
            std::cout << "Clear pool of " << typeid(T).name() << std::endl;
            for (typename std::deque<T*>::iterator it = m_free.begin(); it != m_free.end(); ++it)
			{
				operator delete ((void*)*it);
			}
			m_free.clear();
		}
	};
}

#endif
