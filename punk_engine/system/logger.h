/*
File: Logger.h
Author: Nickolai Abramov
Desc: Special for making logs
*/

#ifndef _H_LOGGER
#define _H_LOGGER

#include "singletone.h"
#include "string.h"
#include "buffer.h"

#define LOG_LOCATION __FILEW__, ::System::string::Convert(__LINE__), ::System::string(__FUNCSIG__)
#define LOG_LOCATION_STRING ::System::string::Format(L" %s(%d): %s", __FILEW__, __LINE__, ::System::string(__FUNCSIG__).Data())
#define SMART_LOG(A, B, COND) if ((A) == (COND)) B;

namespace System
{
	SingletoneInterface(Logger, MODULE_SYSTEM)

	class MODULE_SYSTEM Logger : public Singletone(Logger)
	{	
		static string m_filename;
		static const int MaxMessageLength = 8192;
	public:
		Logger();
		~Logger();
		void WriteDebugMessage(const string& msg, const string& file = L"", const string& line = L"", const string& function = L"");
		void WriteMessage(const string& msg, const string& file = L"", const string& line = L"", const string& function = L"");
		void WriteWarning(const string& msg, const string& file = L"", const string& line = L"", const string& function = L"");
		void WriteError(const string& msg, const string& file = L"", const string& line = L"", const string& function = L"");
		void DisplayToConsole(bool value);
		void DisplayToFile(bool value);

	private:
		void Write(const string& msg);
		bool displayToConsole;
		bool displayToFile;
		Buffer buffer;
	};
}

#endif // _H_LOGGER
