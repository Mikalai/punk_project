#ifdef _WIN32
#include <process.h>
#endif
#include "thread.h"

namespace System
{
	Thread::~Thread()
	{
		Destroy();
	}

	bool Thread::Create(unsigned (__stdcall *thread_func)(void*), void* data, unsigned stack)
	{
#ifdef _WIN32
		if (Handle() != NULL)
			return false;
		Handle() = (HANDLE)_beginthreadex(0, stack, thread_func, data, CREATE_SUSPENDED, 0);
		if (Handle() != INVALID_HANDLE_VALUE)
			return true;
		return false;
#endif	//	_WIN32
	}

	bool Thread::Join()
	{
#ifdef _WIN32
		return WaitForSingleObject(Handle(), INFINITE) != WAIT_FAILED;
#endif	//	_WIN32
	}

	bool Thread::Resume()
	{
#ifdef _WIN32
		return ResumeThread(Handle()) != (DWORD)-1;
#endif	//	_WIN32
	}

	bool Thread::Destroy()
	{
#ifdef _WIN32
		if (Handle())
		{
			CloseHandle(Handle());
			Handle() = NULL;
		}
		return true;
#endif	//	_WIN32
	}
}
