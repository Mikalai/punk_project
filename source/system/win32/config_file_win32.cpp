#ifdef _WIN32


#include <windows.h>
#include "config_file_win32.h"
#include "../logger.h"
#include "../singletone.h"
#include "../error.h"

namespace System
{
	ConfigFile::ConfigFile() : m_filename(L"punk_engine")
	{
	}

	ConfigFile::~ConfigFile()
	{
		//Close();
	}

	bool ConfigFile::Open(const System::string &filename)
	{
		DWORD result;
		HKEY software;
		m_filename = filename;
		if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, L"Software", 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &software, &result))
		{
			out_error() << L"Can't open 'Software' in registry" << std::endl;			
			return false;
		}

		if (ERROR_SUCCESS != RegCreateKeyEx(software, m_filename.Data(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &m_key, &result))
		{
			out_error() << string::Format(L"Can't create/open %s in registry", m_filename.Data()) << std::endl;
			return false;
		}
		out_message() << string::Format(L"Config file %s has been opened", m_filename.Data()) << std::endl;
		return true;
	}

	void ConfigFile::Close()
	{
		RegCloseKey(m_key);
		out_message() << string::Format(L"Config file %s has been closed", m_filename.Data()) << std::endl;
	}

	bool ConfigFile::ReadOptionString(const string& option, string& res)
	{		
		DWORD type;
		DWORD size;
		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size))
		{
			out_error() << string::Format(L"Can't get value %s from registry", option.Data()) << std::endl;
			return false;
		}

		if (type != REG_SZ)
		{
			out_error() << string::Format(L"Bad type of %s. Expected string", option.Data()) << std::endl;
			return false;
		}

		wchar_t* buf = new wchar_t[size];
		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, buf, &size))
		{
			out_error() << string::Format(L"Can't get value %s from registry", option.Data()) << std::endl;
			delete[] buf;
			return false;
		}
		res = string(buf);
		delete buf;
		return true;
	}

	bool ConfigFile::ReadOptionInt(const string& option, int& res)
	{
		DWORD type;
		DWORD size;
		LONG err;
		if (ERROR_SUCCESS != (err = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size)))
		{
			if (err == ERROR_FILE_NOT_FOUND)
			{
				out_error() << "File not found" << std::endl;
				return false;
			}
			out_error() << string::Format(L"Can't get value %s from registry", option.Data());
			throw SystemError(L"Fatal error");
		}

		if (type != REG_DWORD)
		{
			out_error() << string::Format(L"Bad type of %s. Expected int", option.Data()) << std::endl;
			return false;
		}

		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_DWORD, &type, (void*)&res, &size))
		{
			out_error() << string::Format(L"Can't get value %s from registry", option.Data()) << std::endl;
			return false;
		}
		return true;
	}

	bool ConfigFile::WriteOptionString(const string& option, const string& value)
	{
		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_SZ, (const BYTE*)value.Data(), (value.Length()+1)*sizeof(wchar_t)))
		{
			out_error() << string::Format(L"Can't write option %s with value %s into %s", option.Data(), value.Data(), m_filename.Data())  << std::endl;
			return false;
		}
		return true;
	}

	bool ConfigFile::WriteOptionInt(const string& option, int value)
	{
		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_DWORD, (const BYTE*)&value, sizeof(int)))
		{
			out_error() << string::Format(L"Can't write option %s with value %d into %s", option.Data(), value, m_filename.Data()) << std::endl;
			return false;
		}
		return true;
	}

	bool ConfigFile::IsExistOption(const string& option)
	{
		DWORD type;
		DWORD size;
		LONG err;
		if (ERROR_SUCCESS != (err = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size)))
		{
			if (err == ERROR_FILE_NOT_FOUND)
			{
				 out_error() << "File not found" << std::endl;
				 return false;
			}
			out_error() << L"Fatal error" << std::endl;
		}
		return true;
	}
}

#endif