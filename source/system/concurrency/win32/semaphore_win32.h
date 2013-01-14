#ifndef _H_PUNK_SYSTEM_SEMAPTHORE_WIN32
#define _H_PUNK_SYSTEM_SEMAPTHORE_WIN32

#include "../../../config.h"
#include "os_handle.h"

namespace System
{
	class PUNK_ENGINE Semaphore : public OsSync
	{
	public:		
		bool Create(long max_count);
		bool Destroy();
		bool Release(long count = 1);
		bool Wait(long time = INFINITE);
	};
}

#endif	//	_H_PUNK_SYSTEM_SEMAPTHORE_WIN32