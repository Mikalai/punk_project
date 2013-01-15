#ifdef _WIN32

#include "thread_mutex_win32.h"

namespace System
{
	ThreadMutex::ThreadMutex()
	{
		Create();
	}	

	ThreadMutex::~ThreadMutex()
	{
		Destroy();
	}

	bool ThreadMutex::Create()
	{
		return InitializeCriticalSectionAndSpinCount(&m_mutex, 4000) != FALSE;
	}

	void ThreadMutex::Destroy()
	{
		DeleteCriticalSection(&m_mutex);
	}

	void ThreadMutex::Lock()
	{
		EnterCriticalSection(&m_mutex);
	}

	bool ThreadMutex::TryLock()
	{
		return TryEnterCriticalSection(&m_mutex) != FALSE;
	}

	void ThreadMutex::Unlock()
	{
		LeaveCriticalSection(&m_mutex);
	}
}

#endif	//	_WIN32