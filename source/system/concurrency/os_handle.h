#ifndef _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
#define _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE

#ifdef _WIN32
#include <Windows.h>
#elif defined __gnu_linux__
#include <pthread.h>
#endif

#include "../../config.h"

namespace System
{

#ifdef _WIN32
	class PUNK_ENGINE_PUBLIC OsHandle
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
    class PUNK_ENGINE_PUBLIC OsHandle
    {
    public:
        OsHandle() {}
        const pthread_t* ThreadHandle() const { return &m_thread; }
        pthread_t* ThreadHandle() { return &m_thread; }
    private:
        union
        {
            pthread_t m_thread;
        };

    };
#endif  //  __linux__

}

#endif	//	 _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
