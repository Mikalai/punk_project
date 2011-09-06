#include <Windows.h>
#include "echo_module\echo_module.h"
#include "console_interpretator.h"

namespace Translator
{
	void* GetProcAddress(const System::string& name)
	{
#ifdef _WIN32
		HMODULE lib = LoadLibraryW(name.Data());
		void* res = ::GetProcAddress(lib, "GetPunkModule");
		//FreeLibrary(lib);
		GetLastError();
		return res;
#endif
#ifdef __linux__
		void* res = (void*)glXGetProcAddress((unsigned char*)name);
		return res;
#endif
	}

	Interpretator::Interpretator()
	{
		ModuleInterface* echo = new EchoModule();
		m_modules[echo->GetKeyword()] = echo;
	}

	Interpretator::~Interpretator()
	{
		for (auto i = m_modules.begin(); i != m_modules.end(); ++i)
		{
			delete i->second;
		}
	}

	bool Interpretator::LoadModule(const System::string& module)
	{
/*		GetModule GetPunkModule = (GetModule)GetProcAddress(module);
		if (GetPunkModule)
		{
			ModuleInterface* m = GetPunkModule();
			wprintf(L"Module loaded\n%s v%s\nDescription: %s", m->GetKeyword().Data(), m->GetVersion().Data(), m->GetDescription().Data());
			m_modules[m->GetKeyword()] = m;
			return true;
		}		*/
		return false;
	}

	bool Interpretator::Process(const System::string& message)
	{
		std::vector<System::string> strings = message.Split(L" ");

		if (strings.empty())
			return false;

		for (auto i = m_modules.begin(); i != m_modules.end(); ++i)
		{
			if (i->first == strings[0])
			{
				return i->second->Process(message);
			}
		}
		/**/
		return true;
	}
}