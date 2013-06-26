#include "environment.h"
#include "folder.h"

namespace System
{
	Environment* Environment::m_instance;

	Environment* Environment::Instance()
	{
		if (!m_instance)
			m_instance = new Environment;
		return m_instance;
	}

	void Environment::Destroy()
	{
		delete m_instance;
		m_instance = 0;
	}
	
	Environment::Environment()
	{
		//System::ConfigFile file;
		//file.Open(System::Window::Instance()->GetTitle());
		//	file.WriteOptionString(L"data", L"d:\\project\\data\\");	
		//if (!file.IsExistOption(L"data"))
		//	
		//file.Close();
	}

	const string Environment::GetCurrentFolder()
	{
		return Folder::GetCurrentFolder();
	}

	void Environment::SetCurrentFolder(const string& dir)
	{
		Folder::SetCurrentFolder(dir);
	}

	const string Environment::GetFontFolder()
	{
        return GetCurrentFolder() + L"/../../data/fonts/";
		//return GetCurrentFolder() + L"fonts\\";
	}

	const string Environment::GetModelFolder()
	{
        return GetCurrentFolder() + L"/../../data/models/";
		//return GetCurrentFolder() + L"models\\";
	}

	const string Environment::GetMapFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\maps\\";
		//return GetCurrentFolder() + L"maps\\";
	}

	const string Environment::GetSaveFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\saves\\";
		//return GetCurrentFolder() + L"saves\\";
	}

	const string Environment::GetTextureFolder()
	{
#ifdef _WIN32
        return GetCurrentFolder() + L"\\..\\..\\data\\textures\\";
        //return GetCurrentFolder() + L"textures\\";
#elif defined __gnu_linux__
        return GetCurrentFolder() + L"/../../data/textures/";
#endif
	}

	const string Environment::GetQuestFolder() 
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\quests\\";
		//return GetCurrentFolder() + L"quests\\";
	}

	const string Environment::GetSoundFolder() 
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\audio\\";
		//return GetCurrentFolder() + L"audio\\";
	}

	const string Environment::GetShaderFolder()
	{
#ifdef __gnu_linux__
        return GetCurrentFolder() + L"/../../data/shaders/";
#endif
		//return GetCurrentFolder() + L"shaders\\";
	}
	
	const string Environment::GetArmatureFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\armatures\\";
		//return GetCurrentFolder() + L"armatures\\";
	}

	const string Environment::GetWeaponFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\weapons\\";
		//return GetCurrentFolder() + L"weapons\\";
	}

	const string Environment::GetOpenCLFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\opencl\\";
		//return GetCurrentFolder() + L"weapons\\";
	}
}
