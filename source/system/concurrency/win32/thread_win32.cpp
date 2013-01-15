#ifdef _WIN32

#include <process.h>
#include "thread_win32.h"

namespace System
{
	Thread::~Thread()
	{
		Destroy();
	}

	bool Thread::Create(unsigned (__stdcall *thread_func)(void*), void* data, unsigned stack)
	{
		if (Handle() != NULL)
			return false;
		Handle() = (HANDLE)_beginthreadex(0, stack, thread_func, data, CREATE_SUSPENDED, 0);
		if (Handle() != INVALID_HANDLE_VALUE)
			return true;
		return false;
	}

	bool Thread::Join()
	{
		return WaitForSingleObject(Handle(), INFINITE) != WAIT_FAILED;
	}

	bool Thread::Resume()
	{
		ResumeThread(Handle()) != (DWORD)-1;
	}

	bool Thread::Destroy()
	{
		if (Handle())
		{
			CloseHandle(Handle());
			Handle() = NULL;
		}
		return true;
	}
}

#endif	//	_WIN32