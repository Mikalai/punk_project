//#ifdef _WIN32
//#ifndef NOMINMAX
//#define NOMINMAX
//#endif	//	NOMINMAX
//#include <windows.h>
//#endif	//	_WIN32

//#include "config_file.h"
//#include "logger.h"
//#include "errors/module.h"

//namespace System
//{
//	ConfigFile::ConfigFile() : m_filename(L"PUNK_ENGINE_PUBLIC")
//	{
//	}

//	ConfigFile::~ConfigFile()
//	{
//		//Close();
//	}

//	bool ConfigFile::Open(const System::string &filename)
//	{
//#ifdef _WIN32
//		HRESULT error;
//		DWORD result;
//		HKEY software;
//		m_filename = filename;
//        RegCreateKeyEx(HKEY_CURRENT_USER, L"Software", 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &software, &result);
//		CHECK_SYS_ERROR_CODE(error, L"Can't open 'Software' in registry");

//        RegCreateKeyEx(software, m_filename.Data(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &m_key, &result);
//		CHECK_SYS_ERROR_CODE(error, string("Can't create/open %s in registry", m_filename.Data()));

//		out_message() << string("Config file %s has been opened", m_filename.Data()) << std::endl;
//#endif	//	_WIN32
//		return true;
//	}

//	void ConfigFile::Close()
//	{
//#ifdef _WIN32
//		RegCloseKey(m_key);
//		out_message() << string("Config file %s has been closed", m_filename.Data()) << std::endl;
//#endif	//	_WIN32
//	}

//	bool ConfigFile::ReadOptionString(const string& option, string& res)
//	{
//#ifdef _WIN32
//		HRESULT error;
//		DWORD type;
//		DWORD size;
//        RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size);
//		CHECK_SYS_ERROR_CODE(error, string("Can't get value %s from registry", option.Data()));

//		if (type != REG_SZ)
//			throw PunkInvalidArgumentException(string("Bad type of %s. Expected string", option.Data()));

//		std::vector<wchar_t> buf(size);
//        RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, &buf[0], &size);
//		CHECK_SYS_ERROR_CODE(error, string("Can't get value %s from registry", option.Data()));
//		res = string(&buf[0]);
//#endif	//	_WIN32
//		return true;
//	}

//	bool ConfigFile::ReadOptionInt(const string& option, int& res)
//	{
//#ifdef _WIN32
//		HRESULT error;
//		DWORD type;
//		DWORD size;
//        RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size);
//		CHECK_SYS_ERROR_CODE(error, L"Can't read key " + option);

//		if (type != REG_DWORD)
//			throw PunkInvalidArgumentException(string("Bad type of %s. Expected dword", option.Data()));

//        RegGetValue(m_key, 0, option.Data(), RRF_RT_DWORD, &type, (void*)&res, &size);
//		CHECK_SYS_ERROR_CODE(error, string("Can't get value %s from registry", option.Data()));
//#endif	//	_WIN32
//		return true;
//	}

//	bool ConfigFile::WriteOptionString(const string& option, const string& value)
//	{
//#ifdef _WIN32
//		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_SZ, (const BYTE*)value.Data(), (value.Length()+1)*sizeof(wchar_t)))
//		{
//			out_error() << string("Can't write option %s with value %s into %s", option.Data(), value.Data(), m_filename.Data())  << std::endl;
//			return false;
//		}
//#endif	//	_WIN32
//		return true;
//	}

//	bool ConfigFile::WriteOptionInt(const string& option, int value)
//	{
//#ifdef _WIN32
//		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_DWORD, (const BYTE*)&value, sizeof(int)))
//		{
//			out_error() << string("Can't write option %s with value %d into %s", option.Data(), value, m_filename.Data()) << std::endl;
//			return false;
//		}
//#endif	//	_WIN32
//		return true;
//	}

//	bool ConfigFile::IsExistOption(const string& option)
//	{
//#ifdef _WIN32
//		DWORD type;
//		DWORD size;
//		LONG err;
//		if (ERROR_SUCCESS != (err = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size)))
//		{
//			if (err == ERROR_FILE_NOT_FOUND)
//			{
//				 out_error() << "File not found" << std::endl;
//				 return false;
//			}
//			out_error() << L"Fatal error" << std::endl;
//		}
//#endif	//	_WIN32
//		return true;
//	}
//}
