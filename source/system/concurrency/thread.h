#ifndef _H_PUNK_THREAD
#define _H_PUNK_THREAD

#include "../../config.h"
#include "os_handle.h"

namespace System
{
	class PUNK_ENGINE_API Thread : public OsHandle
	{
	public:
#ifdef _WIN32
        bool Create(unsigned (PUNK_STDCALL *thread_func)(void*), void* data = 0, unsigned stack = 4096);
#elif defined __gnu_linux__
        bool Create(void* (PUNK_STDCALL *thread_func)(void*), void* data = 0, unsigned stack = 4096);
#endif
		bool Join();
		bool Resume();
		bool Destroy();
		//bool Terminate();
		~Thread();

        static Thread GetOwnThread();
        /**
         * @brief Sleep. Force to sleep current thread for time milliseconds.
         * @param time
         */
        static void Sleep(unsigned time);
	};
}

#endif	//	_H_PUNK_THREAD
