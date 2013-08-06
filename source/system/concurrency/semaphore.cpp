#ifdef __gnu_linux__
#include <semaphore.h>
#endif

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
#elif defined __gnu_linux__
        sem_init(SemaphoreHandle(), 0, max_count);
#endif
	}

	bool Semaphore::Destroy()
	{		
#ifdef _WIN32
		if (Handle())
			CloseHandle(Handle());
		return true;
#elif defined __gnu_linux__
        return sem_destroy(SemaphoreHandle()) == 0;
#endif
	}

	bool Semaphore::Release(long count)
	{
#ifdef _WIN32
		auto res = ReleaseSemaphore(Handle(), count, 0);
		return res == TRUE;
#elif defined __gnu_linux__
        bool result = true;
        while (count--)
            result &= sem_post(SemaphoreHandle()) == 0;
        return result;
#endif
	}

	bool Semaphore::Wait(long time)
	{
#ifdef _WIN32
		if (Handle())
			return WaitForSingleObject(Handle(), time) == TRUE;
		return false;
#elif defined __gnu_linux__
        if (time == PUNK_INFINITE)
            return sem_wait(SemaphoreHandle()) == 0;
        else
        {
            timespec t;
            //  convert milliseconds time to timespec
            t.tv_sec = time / 1000; //    seconds
            t.tv_nsec = (time % 1000) * 1000000;    //  nanosecs
            return sem_timedwait(SemaphoreHandle(), &t) == 0;
        }
#endif
	}
}

