#include "semaphore.h"

namespace System
{
	Semaphore::~Semaphore()
	{
#ifdef _WIN32
		CloseHandle(Handle());
#endif	//	_WIN32
	}

	bool Semaphore::Create(long max_count)
	{
#ifdef _WIN32
		if (Handle())
			Destroy();
		Handle() = CreateSemaphore(0, 0, max_count, nullptr);
		return NULL != Handle();
#endif	//  _WIN32
	}

	bool Semaphore::Destroy()
	{		
#ifdef _WIN32
		if (Handle())
			CloseHandle(Handle());
		return true;
#endif	//  _WIN32
	}

	bool Semaphore::Release(long count)
	{
#ifdef _WIN32
		auto res = ReleaseSemaphore(Handle(), count, 0);
		return res == TRUE;
#endif	//	_WIN32
	}

	bool Semaphore::Wait(long time)
	{
#ifdef _WIN32
		if (Handle())
			return WaitForSingleObject(Handle(), time) == TRUE;
		return false;
#endif	//	_WIN32
	}
}

