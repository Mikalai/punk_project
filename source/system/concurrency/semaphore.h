#ifndef _H_PUNK_SYSTEM_SEMAPTHORE_WIN32
#define _H_PUNK_SYSTEM_SEMAPTHORE_WIN32

#include "../../config.h"
#include "os_handle.h"

namespace System
{
	class PUNK_ENGINE_API Semaphore : public OsHandle
	{
	public:		
		bool Create(long max_count);
		bool Destroy();
		bool Release(long count = 1);
        /**
         * @brief Wait
         * @param time - time to wait in milliseconds.
         * @return true if all ok, false otherwise.
         */
        bool Wait(long time = PUNK_INFINITE);
		~Semaphore();
	};
}

#endif	//	_H_PUNK_SYSTEM_SEMAPTHORE_WIN32
