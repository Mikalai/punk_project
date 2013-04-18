#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include <string.h>
#include "../config.h"
#include <deque>
#include "pool_manager.h"

namespace System
{
	template<class T>
	class Pool
	{
		std::deque<void*> m_free;
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

		void* Alloc()
		{
			if (m_free.empty())
			{
//				out_message() << "Allocation requested for " << typeid(T).name() << std::endl;
				void* chunk = operator new(sizeof(T));
				//	clear memory
				::memset(chunk, 0, sizeof(T));
				return chunk;
			}
			void* chunk = m_free.front();
			//	clear memory
			memset(chunk, 0, sizeof(T));
			m_free.pop_front();
			return chunk;
		}

		void Free(void* value)
		{
			//out_message() << "Free requested" << std::endl;
			m_free.push_back(value);
		}

		void Clear()
		{
			for (std::deque<void*>::iterator it = m_free.begin(); it != m_free.end(); ++it)
			{
				delete *it;
			}
			m_free.clear();
		}
	};
}

#endif
