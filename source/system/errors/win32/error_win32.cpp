#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "error_win32.h"
#include "../exceptions.h"

namespace System
{
	void CheckOSError(const System::string& msg)
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
			throw OSException(error);
		}		
	}

	void CheckOSError(LONG code, const System::string& msg)
	{
		string error;

		if (code != S_OK)
		{
			HLOCAL hLocal = 0;
			if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
			    error = string((wchar_t*)p) + string::Format(L"(Code: 0x%X) (MS Windows)", code);
				LocalFree(hLocal);
			}
			else
			{
				error = L"Unknown error from GetLastError()";
			}
			throw OSException(error);
		}		
	}

}

#endif
