#include <windows.h>
#include "environment_win32.h"

namespace System
{
	string Environment::GetCurrentDirectory()
	{
		wchar_t buffer[MAX_PATH];
		::GetCurrentDirectoryW(MAX_PATH, buffer);
		return string(buffer);
	}

	void Environment::SetCurrentDirectory(const string& dir)
	{
		::SetCurrentDirectoryW(dir.Data());
	}
}