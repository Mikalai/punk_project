#ifdef _WIN32

#define NOMINMAX
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

	void ConfigFile::Open(const System::string &filename)
	{
		DWORD result;
		HKEY software;
		m_filename = filename;
		if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, L"Software", 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &software, &result))
		{
			Logger::Instance()->WriteError(L"Can't open 'Software' in registry", LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}

		if (ERROR_SUCCESS != RegCreateKeyEx(software, m_filename.Data(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &m_key, &result))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't create/open %s in registry", m_filename.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}
		Logger::Instance()->WriteMessage(string::Format(L"Config file %s has been opened", m_filename.Data()));
	}

	void ConfigFile::Close()
	{
		RegCloseKey(m_key);
		Logger::Instance()->WriteMessage(string::Format(L"Config file %s has been closed", m_filename.Data()));
	}

	string ConfigFile::ReadOptionString(const string& option)
	{		
		DWORD type;
		DWORD size;
		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't get value %s from registry", option.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}

		if (type != REG_SZ)
		{
			Logger::Instance()->WriteError(string::Format(L"Bad type of %s. Expected string", option.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}

		wchar_t* buf = new wchar_t[size];
		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, buf, &size))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't get value %s from registry", option.Data()), LOG_LOCATION);
			delete[] buf;
			throw SystemError(L"Fatal error");
		}
		string res(buf);
		delete buf;
		return res;
	}

	int ConfigFile::ReadOptionInt(const string& option)
	{
		DWORD type;
		DWORD size;
		LONG err;
		if (ERROR_SUCCESS != (err = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size)))
		{
			if (err == ERROR_FILE_NOT_FOUND)
				throw FileNotFound();
			Logger::Instance()->WriteError(string::Format(L"Can't get value %s from registry", option.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}

		if (type != REG_DWORD)
		{
			Logger::Instance()->WriteError(string::Format(L"Bad type of %s. Expected int", option.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}

		int res;
		if (ERROR_SUCCESS != RegGetValue(m_key, 0, option.Data(), RRF_RT_DWORD, &type, (void*)&res, &size))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't get value %s from registry", option.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}
		return res;
	}

	void ConfigFile::WriteOptionString(const string& option, const string& value)
	{
		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_SZ, (const BYTE*)value.Data(), (value.Length()+1)*sizeof(wchar_t)))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't write option %s with value %s into %s", option.Data(), value.Data(), m_filename.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}
	}

	void ConfigFile::WriteOptionInt(const string& option, int value)
	{
		if (ERROR_SUCCESS != RegSetValueEx(m_key, option.Data(), 0, REG_DWORD, (const BYTE*)&value, sizeof(int)))
		{
			Logger::Instance()->WriteError(string::Format(L"Can't write option %s with value %d into %s", option.Data(), value, m_filename.Data()), LOG_LOCATION);
			throw SystemError(L"Fatal error");
		}
	}

	bool ConfigFile::IsExistOption(const string& option)
	{
		DWORD type;
		DWORD size;
		LONG err;
		if (ERROR_SUCCESS != (err = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size)))
		{
			if (err == ERROR_FILE_NOT_FOUND)
				return false;			
			throw SystemError(L"Fatal error");
		}
		return true;
	}
}

#endif