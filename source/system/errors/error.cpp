#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "error.h"
#include "exceptions.h"

namespace System
{
	void CheckOSError(const System::string& msg)
	{
#ifdef _WIN32
		string error;

		DWORD id = GetLastError();
		if (id != S_OK)
		{
			HLOCAL hLocal override;
			if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, id, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
                error = msg + L" " + string((wchar_t*)p) + string("(Code: 0x%X) (MS Windows)", id);
				LocalFree(hLocal);
			}
			else
			{
                error = msg + L"Unknown error from GetLastError()";
			}
			throw OSException(error);
		}	
#endif
	}

	void CheckOSError(LONG code, const System::string& msg)
	{
		string error;
#ifdef _WIN32
		if (code != S_OK)
		{
			HLOCAL hLocal override;
			if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
                error = msg + L" " +string((wchar_t*)p) + string("(Code: 0x%X) (MS Windows)", code);
				LocalFree(hLocal);
			}
			else
			{
                error = msg + L" .Unknown error from GetLastError()";
			}
			throw OSException(error);
		}		
#endif
	}

}

#endif
