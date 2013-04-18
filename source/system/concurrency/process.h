#ifndef _H_PUNK_PROCESS
#define _H_PUNK_PROCESS

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif	//	_WIN32

#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE Process
	{

#ifdef _WIN32
		STARTUPINFOEXW m_startup_info;
		PROCESS_INFORMATION m_process_info;
#endif	// _WIN32

		bool m_is_launched;
	public:
		Process();
		~Process();

		bool Start(string& cmd_line);
		void Terminate();
	};
}

#endif	//	_H_PUNK_PROCESS
