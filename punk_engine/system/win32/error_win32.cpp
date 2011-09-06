#ifdef _WIN32

#include "error_win32.h"
#include "stack_trace_win32.h"

namespace System
{
	SystemError::SystemError() : std::exception() 
	{
		Stack stack;
		message += L"OS error:\n";
		message += CheckOSError();
		message += L"Stack trace:\n";
		message += stack.GetStackTrace();
	}

	SystemError::~SystemError() throw() {}

	SystemError::SystemError(wchar_t* msg) : std::exception(), message(msg) 
	{
		Stack stack;
		message += L"\nOS error:\n";
		message += CheckOSError();
		message += L"Stack trace:\n";
		message += stack.GetStackTrace();
	}        

	SystemError::SystemError(const string& msg) : std::exception(), message(msg) 
	{
		Stack stack;
		message += L"\nOS error:\n";
		message += CheckOSError();
		message += L"Stack trace:\n";
		message += stack.GetStackTrace();
	}

	const string& SystemError::Message() const throw()
	{
		return message;
	}

	const char* SystemError::what() const throw()
	{
		return "No comments";
	}

	string SystemError::CheckOSError()
	{
		string error;

		DWORD id = GetLastError();
		if (id != S_OK)
		{
			HLOCAL hLocal = 0;
			if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, id, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
			    error = string((wchar_t*)p) + string::Format(L"(Code: 0x%X) (MS Windows)", id);
				LocalFree(hLocal);
			}
			else
			{
				error = L"Unknown error from GetLastError()";
			}
		}
		return error;
	}
}

#endif
