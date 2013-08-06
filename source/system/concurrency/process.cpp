#include "process.h"

namespace System
{
	Process::Process()
	{

#ifdef _WIN32
		memset(&m_startup_info, 0, sizeof(m_startup_info));
		m_startup_info.StartupInfo.cb = sizeof(m_startup_info);
#endif	//	_WIN32

	}

	Process::~Process()
	{
#ifdef _WIN32
		CloseHandle(m_process_info.hThread);
		CloseHandle(m_process_info.hProcess);		
#endif	//	_WIN32
	}

	bool Process::Start(string& cmd_line)
	{
#ifdef _WIN32
        wchar_t buf[MAX_PATH];
        wcscpy_s(buf, MAX_PATH, cmd_line.ToStdWString().c_str());
        return m_is_launched = (TRUE == CreateProcessW(NULL, buf, NULL, NULL, TRUE, 0, 0, 0, &m_startup_info.StartupInfo, &m_process_info));
#endif	//	_WIN32
	}

	void Process::Terminate()
	{
		if (m_is_launched)
		{
#ifdef _WIN32
			TerminateProcess(m_process_info.hProcess, 0);
			WaitForSingleObject(m_process_info.hProcess, INFINITE);
#endif	//	_WIN32
		}
	}
}
