#include <windows.h>
#include "environment_win32.h"
#include "config_file_win32.h"
#include "window_win32.h"

namespace System
{
	string Environment::GetCurrentFolder()
	{
		ConfigFile conf;
		conf.Open(System::Window::GetInstance()->GetTitle());
		string folder = conf.ReadOptionString(L"data");
		conf.Close();
		return folder;
	}

	void Environment::SetCurrentFolder(const string& dir)
	{
		::SetCurrentDirectory(dir.Data());
	}

	string Environment::GetFontFolder()
	{
		return GetCurrentFolder() + L"fonts\\";
	}

	string Environment::GetModelFolder()
	{
		return GetCurrentFolder() + L"models\\";
	}

	string Environment::GetMapFolder()
	{
		return GetCurrentFolder() + L"maps\\";
	}

	string Environment::GetSaveFolder()
	{
		return GetCurrentFolder() + L"saves\\";
	}

	string Environment::GetTexutreFolder()
	{
		return GetCurrentFolder() + L"textures\\";
	}

	string Environment::GetQuestFolder() 
	{
		return GetCurrentFolder() + L"quests\\";
	}

	const string Environment::GetShaderFolder()
	{
		return GetCurrentFolder() + L"shaders\\";
	}
}