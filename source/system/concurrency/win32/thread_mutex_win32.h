#ifndef _H_PUNK_SYSMTE_THREAD_MUTEX_WIN32
#define _H_PUNK_SYSMTE_THREAD_MUTEX_WIN32

#include <Windows.h>
#include "../../../config.h"

namespace System
{
	class PUNK_ENGINE ThreadMutex
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
		CRITICAL_SECTION m_mutex;
	};
}

#endif // _H_PUNK_SYSMTE_THREAD_MUTEX_WIN32