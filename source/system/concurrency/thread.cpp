#ifdef _WIN32
#include <process.h>
#elif defined __gnu_linux__
#include <time.h>
#endif

#include "thread.h"

namespace System
{
	Thread::~Thread()
	{
		Destroy();
	}

#ifdef _WIN32
    bool Thread::Create(unsigned (PUNK_STDCALL *thread_func)(void*), void* data, unsigned stack)
	{
		if (Handle() != NULL)
			return false;
		Handle() = (HANDLE)_beginthreadex(0, stack, thread_func, data, CREATE_SUSPENDED, 0);
		if (Handle() != INVALID_HANDLE_VALUE)
			return true;
		return false;
	}
#endif	//	_WIN32

#ifdef __gnu_linux__
    bool Thread::Create(void *(*thread_func)(void *), void *data, unsigned stack)
    {
        bool result = false;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, stack);
        result = pthread_create(ThreadHandle(), &attr, thread_func, data) != 0;
        pthread_attr_destroy(&attr);
        return result;
   }
#endif

	bool Thread::Join()
	{
#ifdef _WIN32
		return WaitForSingleObject(Handle(), INFINITE) != WAIT_FAILED;
#elif defined __gnu_linux__
        void* result;
        return pthread_join(*ThreadHandle(), &result) == 0;
#endif
	}

	bool Thread::Resume()
	{
#ifdef _WIN32
		return ResumeThread(Handle()) != (DWORD)-1;
#elif   defined __gnu_linux__
        return false;
#endif
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
#elif defined __gnu_linux__
        //  TODO: seems nothing should be placed here
#endif
	}

    Thread Thread::GetOwnThread()
    {
        Thread result;
        *result.ThreadHandle() = pthread_self();
        return result;
    }

    void Thread::Sleep(unsigned time)
    {
#ifdef _WIN32
        ::Sleep(time);
#elif defined __gnu_linux__
        timespec t, rem;
        t.tv_sec = time / 1000;
        t.tv_nsec = (time % 1000) * 1000000;
        nanosleep(&t, &rem);
#endif
    }
}
