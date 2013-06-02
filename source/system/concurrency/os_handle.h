#ifndef _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
#define _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE

#ifdef _WIN32
#include <Windows.h>
#elif defined __gnu_linux__
#include <pthread.h>
#include <semaphore.h>
#endif

#include "../../config.h"

namespace System
{

#ifdef _WIN32
	class PUNK_ENGINE_API OsHandle
	{
	public:
		OsHandle() : m_handle(0) {}		
		const HANDLE& Handle() const { return m_handle; }
		HANDLE& Handle() { return m_handle; }
	private:
		HANDLE m_handle;
	};
#endif	//	_WIN32

#ifdef __linux__
    class PUNK_ENGINE_API OsHandle
    {
    public:
        OsHandle() {}
        const pthread_t* ThreadHandle() const { return &m_thread; }
        pthread_t* ThreadHandle() { return &m_thread; }
        const sem_t* SemaphoreHandle() const { return &m_semaphore; }
        sem_t* SemaphoreHandle() { return &m_semaphore; }
    private:
        union
        {
            pthread_t m_thread;
            sem_t m_semaphore;
        };

    };
#endif  //  __linux__

}

#endif	//	 _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
