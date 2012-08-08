#define NOMINMAX
#include <windows.h>
#include "environment_win32.h"
#include "config_file_win32.h"
#include "window_win32.h"

namespace System
{
	SingletoneImplementation(Environment)

	Environment::Environment()
	{
		System::ConfigFile file;
		file.Open(System::Window::Instance()->GetTitle());
			file.WriteOptionString(L"data", L"d:\\project\\data\\");	
		if (!file.IsExistOption(L"data"))
			
		file.Close();
	}

	const string Environment::GetCurrentFolder()
	{
		ConfigFile conf;
		conf.Open(System::Window::Instance()->GetTitle());
		string folder = conf.ReadOptionString(L"data");
		conf.Close();
		return folder;
	}

	void Environment::SetCurrentFolder(const string& dir)
	{
		::SetCurrentDirectory(dir.Data());
	}

	const string Environment::GetFontFolder()
	{
		return GetCurrentFolder() + L"fonts\\";
	}

	const string Environment::GetModelFolder()
	{
		return GetCurrentFolder() + L"models\\";
	}

	const string Environment::GetMapFolder()
	{
		return GetCurrentFolder() + L"maps\\";
	}

	const string Environment::GetSaveFolder()
	{
		return GetCurrentFolder() + L"saves\\";
	}

	const string Environment::GetTextureFolder()
	{
		return GetCurrentFolder() + L"textures\\";
	}

	const string Environment::GetQuestFolder() 
	{
		return GetCurrentFolder() + L"quests\\";
	}

	const string Environment::GetSoundFolder() 
	{
		return GetCurrentFolder() + L"audio\\";
	}

	const string Environment::GetShaderFolder()
	{
		return GetCurrentFolder() + L"shaders\\";
	}
	
	const string Environment::GetArmatureFolder()
	{
		return GetCurrentFolder() + L"armatures\\";
	}

	const string Environment::GetWeaponFolder()
	{
		return GetCurrentFolder() + L"weapons\\";
	}
}