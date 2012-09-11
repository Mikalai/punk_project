#ifndef _H_PUNK_CONFIG_FILE_WIN32
#define _H_PUNK_CONFIG_FILE_WIN32

#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	class PUNK_ENGINE ConfigFile
	{
		ConfigFile(const ConfigFile&);
		ConfigFile& operator = (const ConfigFile&);
		string m_filename;
		HKEY m_key;
	public:
		ConfigFile();
		~ConfigFile();
		bool Open(const string& filename);
		void Close();
		bool ReadOptionString(const string& option, string& result);
		bool ReadOptionInt(const string& option, int& result);
		bool WriteOptionString(const string& option, const string& value);
		bool WriteOptionInt(const string& option, int value);
		bool IsExistOption(const string& option);
	};
}

#endif