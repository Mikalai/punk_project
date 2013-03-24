#include "process.h"

namespace System
{
	Process::Process()
	{
		memset(&m_startup_info, 0, sizeof(m_startup_info));
		m_startup_info.StartupInfo.cb = sizeof(m_startup_info);
	}

	Process::~Process()
	{
		CloseHandle(m_process_info.hThread);
		CloseHandle(m_process_info.hProcess);		
	}

	bool Process::Start(string& cmd_line)
	{
		return m_is_launched = (TRUE == CreateProcessW(NULL, cmd_line.I_know_what_I_do_just_give_me_the_pointer(), NULL, NULL, TRUE, 0, 0, 0, &m_startup_info.StartupInfo, &m_process_info));
	}

	void Process::Terminate()
	{
		if (m_is_launched)
		{
			TerminateProcess(m_process_info.hProcess, 0);
			WaitForSingleObject(m_process_info.hProcess, INFINITE);
		}
	}
}