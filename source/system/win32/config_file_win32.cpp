#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include "config_file_win32.h"
#include "../logger.h"
#include "../errors/module.h"

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
		LONG error;
		HKEY software;
		m_filename = filename;
		error = RegCreateKeyEx(HKEY_CURRENT_USER, L"Software", 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &software, &result);
		CHECK_SYS_ERROR_CODE(error, L"Can't open 'Software' in registry");

		error = RegCreateKeyEx(software, m_filename.Data(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ|KEY_WRITE, 0, &m_key, &result);
		CHECK_SYS_ERROR_CODE(error, string::Format(L"Can't create/open %s in registry", m_filename.Data()));

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
		LONG error;
		DWORD type;
		DWORD size;
		error = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size);
		CHECK_SYS_ERROR_CODE(error, string::Format(L"Can't get value %s from registry", option.Data()));

		if (type != REG_SZ)
			throw PunkInvalidArgumentException(string::Format(L"Bad type of %s. Expected string", option.Data()));

		std::vector<wchar_t> buf(size);
		error = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, &buf[0], &size);
		CHECK_SYS_ERROR_CODE(error, string::Format(L"Can't get value %s from registry", option.Data()));		
		res = string(&buf[0]);

		return true;
	}

	bool ConfigFile::ReadOptionInt(const string& option, int& res)
	{
		DWORD type;
		DWORD size;
		LONG error;
		error = RegGetValue(m_key, 0, option.Data(), RRF_RT_ANY, &type, 0, &size);
		CHECK_SYS_ERROR_CODE(error, L"Can't read key " + option);

		if (type != REG_DWORD)
			throw PunkInvalidArgumentException(string::Format(L"Bad type of %s. Expected dword", option.Data()));

		error = RegGetValue(m_key, 0, option.Data(), RRF_RT_DWORD, &type, (void*)&res, &size);
		CHECK_SYS_ERROR_CODE(error, string::Format(L"Can't get value %s from registry", option.Data()));
		
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