#ifndef _H_PUNK_SYSMTE_THREAD_MUTEX
#define _H_PUNK_SYSMTE_THREAD_MUTEX

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <pthread.h>
#include <errno.h>
#endif

#include "../../config.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC ThreadMutex
	{
	public:
		
		ThreadMutex();
		~ThreadMutex();

		bool Create();
		void Destroy();
		void Lock();
		bool TryLock();
		void Unlock();		

	private:
#ifdef _WIN32
		CRITICAL_SECTION m_mutex;
#elif defined __gnu_linux__
        pthread_mutex_t m_mutex;
#endif
	};
}

#endif // _H_PUNK_SYSMTE_THREAD_MUTEX
