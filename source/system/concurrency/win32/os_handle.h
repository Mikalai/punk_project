#ifndef _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE_WIN32
#define _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE_WIN32

#include <Windows.h>
#include "../../../config.h"

namespace System
{
	class PUNK_ENGINE OsHandle
	{
	public:
		OsHandle() : m_handle(0) {}		
		const HANDLE& Handle() const { return m_handle; }
		HANDLE& Handle() { return m_handle; }
	private:
		HANDLE m_handle;
	};
}

#endif	//	 _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE_WIN32