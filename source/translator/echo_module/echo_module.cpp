//#include <stdio.h>
//#include "echo_module.h"
//
//namespace Translator
//{
//	EchoModule g_echo_module;
//
//	System::string EchoModule::m_keyword(L"echo");
//	System::string EchoModule::m_version(L"1.0");
//	System::string EchoModule::m_description(L"Simple test for modules developing");
//
//	ModuleInterface* _cdecl GetPunkModule()
//	{
//		return &g_echo_module;
//	}
//
//	const System::string& EchoModule::GetDescription() const
//	{
//		return m_description;
//	}
//
//	const System::string& EchoModule::GetKeyword() const
//	{
//		return m_keyword;
//	}
//
//	const System::string& EchoModule::GetVersion() const
//	{
//		return m_version;
//	}
//
//	bool EchoModule::Process(const System::string& str)
//	{
//		if (str.SubString(0, m_keyword.Length()) != m_keyword)
//			return false;
//		wprintf(L"> %s\n", str.SubString(m_keyword.Length(), str.Length()).Data());
//		return true;
//	}
//}
