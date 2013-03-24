#include "thread_mutex.h"

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
#ifdef _WIN32
		return InitializeCriticalSectionAndSpinCount(&m_mutex, 4000) != FALSE;
#endif	//	_WIN32
	}

	void ThreadMutex::Destroy()
	{
#ifdef _WIN32
		DeleteCriticalSection(&m_mutex);
#endif	//	_WIN32
	}

	void ThreadMutex::Lock()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_mutex);
#endif	//	_WIN32
	}

	bool ThreadMutex::TryLock()
	{
#ifdef _WIN32
		return TryEnterCriticalSection(&m_mutex) != FALSE;
#endif	//	_WIN32
	}

	void ThreadMutex::Unlock()
	{
#ifdef _WIN32
		LeaveCriticalSection(&m_mutex);
#endif //	_WIN32
	}
}
