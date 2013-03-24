#ifndef _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
#define _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE

#ifdef _WIN32
#include <Windows.h>
#endif //	_WIN32

#include "../../config.h"

namespace System
{

#ifdef _WIN32
	class PUNK_ENGINE OsHandle
	{
	public:
		OsHandle() : m_handle(0) {}		
		const HANDLE& Handle() const { return m_handle; }
		HANDLE& Handle() { return m_handle; }
	private:
		HANDLE m_handle;
	};
#endif	//	_WIN32

}

#endif	//	 _H_PUNK_SYSTEM_CONCURRENCY_OS_HANDLE
