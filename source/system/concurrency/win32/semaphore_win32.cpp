#ifdef _WIN32

#include "semaphore_win32.h"

namespace System
{
	Semaphore::~Semaphore()
	{
		CloseHandle(Handle());
	}

	bool Semaphore::Create(long max_count)
	{
		if (Handle())
			Destroy();
		Handle() = CreateSemaphore(0, 0, max_count, nullptr);
		return NULL != Handle();
	}

	bool Semaphore::Destroy()
	{		
		if (Handle())
			CloseHandle(Handle());
		return true;
	}

	bool Semaphore::Release(long count)
	{
		auto res = ReleaseSemaphore(Handle(), count, 0);
		return res == TRUE;
	}

	bool Semaphore::Wait(long time)
	{
		if (Handle())
			return WaitForSingleObject(Handle(), time) == TRUE;
		return false;
	}
}

#endif	//	_WIN32
