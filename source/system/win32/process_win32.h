#ifndef _H_PUNK_PROCESS_WIN32
#define _H_PUNK_PROCESS_WIN32


#include <Windows.h>
#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE Process
	{
		STARTUPINFOEXW m_startup_info;
		PROCESS_INFORMATION m_process_info;
		bool m_is_launched;
	public:
		Process();
		~Process();

		bool Start(string& cmd_line);
		void Terminate();
	};
}

#endif