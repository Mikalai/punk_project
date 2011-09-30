#ifndef _H_PUNK_CONFIG_FILE_WIN32
#define _H_PUNK_CONFIG_FILE_WIN32

#include "../config.h"
#include "string_win32.h"

namespace System
{
	class LIB_SYSTEM ConfigFile
	{
		ConfigFile(const ConfigFile&);
		ConfigFile& operator = (const ConfigFile&);
		string m_filename;
		HKEY m_key;
	public:
		ConfigFile();
		~ConfigFile();
		void Open(const string& filename);
		void Close();
		string ReadOptionString(const string& option);
		int ReadOptionInt(const string& option);
		void WriteOptionString(const string& option, const string& value);
		void WriteOptionInt(const string& option, int value);
		bool IsExistOption(const string& option);
	};
}

#endif