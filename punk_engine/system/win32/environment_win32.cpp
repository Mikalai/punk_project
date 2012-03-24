#include <windows.h>
#include "environment_win32.h"

namespace System
{
	string Environment::GetCurrentFolder()
	{
		wchar_t buffer[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, buffer);
		return string(buffer);
	}

	void Environment::SetCurrentFolder(const string& dir)
	{
		::SetCurrentDirectory(dir.Data());
	}

	string Environment::GetFontFolder()
	{
		return GetCurrentFolder() + L"\\fonts";
	}

	string Environment::GetModelFolder()
	{
		return GetCurrentFolder() + L"\\models";
	}

	string Environment::GetMapFolder()
	{
		return GetCurrentFolder() + L"\\maps";
	}

	string Environment::GetSaveFolder()
	{
		return GetCurrentFolder() + L"\\saves";
	}

	string Environment::GetTexutreFolder()
	{
		return GetCurrentFolder() + L"\\textures";
	}

	string Environment::GetQuestFolder() 
	{
		return GetCurrentFolder() + L"\\quests";
	}
}