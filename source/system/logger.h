#ifndef _H_PUNK_SYSTEM_LOGGER
#define _H_PUNK_SYSTEM_LOGGER

#include <memory>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "../config.h"
//#include "stack_trace.h"
#include "input/console.h"
#include "clock.h"
#include "../string/string.h"

namespace System
{
	enum class LoggerType { No, Message, Warning, Error };

	struct PUNK_ENGINE Streamer
	{
	private:
		typedef std::basic_ostream<wchar_t, std::char_traits<wchar_t>> _Myt;
		typedef std::basic_ios<wchar_t, std::char_traits<wchar_t>> _Myios;
	public:
		Streamer();
		Streamer& operator << (const string& s);
		Streamer& operator << (const char* v);
		Streamer& operator << (const wchar_t* v);
		Streamer& operator << (const std::string& v);
		Streamer& operator << (char v);
		Streamer& operator << (wchar_t v);
		Streamer& operator << (unsigned char v);
		Streamer& operator << (short v);
		Streamer& operator << (unsigned short v);
		Streamer& operator << (long v);
		Streamer& operator << (unsigned long v);
		Streamer& operator << (int v);
		Streamer& operator << (unsigned int v);
		Streamer& operator << (__int64 v);
		Streamer& operator << (unsigned __int64 v);
		Streamer& operator << (float v);
		Streamer& operator << (double v);
        Streamer& operator << (long double v);
		Streamer& operator << (_Myt& (__cdecl *_Pfn)(_Myt&));
		Streamer& operator << (_Myios& (__cdecl *_Pfn)(_Myios&));
		Streamer& operator << (std::ios_base& (__cdecl *_Pfn)(std::ios_base&));
		static Streamer& Instance();
		static void Destroy();

	private:
		static std::auto_ptr<Streamer> m_instance;

		std::ofstream m_stream;
	};

    template<LoggerType type> class LoggerBase;

    template<> class LoggerBase<LoggerType::No>
    {
    protected:
		void Header()
		{
			Console::Instance()->SetTextColor(Console::COLOR_WHITE);
			Streamer::Instance() << Clock::SysTimeNowAsLocal();
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}
    };

    template<> class LoggerBase<LoggerType::Message>
    {
    protected:
		void Header()
		{
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGREEN);
			Streamer::Instance() << Clock::SysTimeNowAsLocal() << L": Message: ";
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}
    };

    template<> class LoggerBase<LoggerType::Warning>
    {
    protected:
    	void Header()
		{
			Console::Instance()->SetTextColor(Console::COLOR_YELLOW);
			Streamer::Instance() << Clock::SysTimeNowAsLocal() << L": Warning: ";
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}
    };

	template<>
	class LoggerBase<LoggerType::Error>
	{
    protected:
	    void Header()
		{
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTRED);
			Streamer::Instance()<< Clock::SysTimeNowAsLocal() << ": Error: ";
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}
	};

	//	wired message outputer, suitable only for ASCII symbols
	template<LoggerType type>
	class Logger : protected LoggerBase<type>
	{
	public:
		Logger() {}

	public:
		Streamer& operator () ()
		{
			LoggerBase<type>::Header();
			return m_stream;
		}

	private:
		Streamer m_stream;
	};
}

class Tab
{
	static int m_offset;
public:
	static const Tab Inc() { m_offset++; return Tab(); }
	static const Tab Dec() { m_offset--; return Tab(); }
	friend std::wostream& operator << (std::wostream& stream, const Tab& value);
};


inline std::wostream& operator << (std::wostream& stream, const Tab& value)
{
	if (Tab::m_offset)
		stream << std::wstring(2*Tab::m_offset, L' ');
	return stream;
}


//
//	global staff fro printing messages, warnings and errors to console and to log file
//
#ifdef _DEBUG
extern PUNK_ENGINE System::Logger<System::LoggerType::Message> out_message;
extern PUNK_ENGINE System::Logger<System::LoggerType::Warning> out_warning;
extern PUNK_ENGINE System::Logger<System::LoggerType::Warning> out_error;
#else
extern PUNK_ENGINE System::Logger<System::LOG_MESSAGE> out_message;
extern PUNK_ENGINE System::Logger<System::LOG_WARNING> out_warning;
extern PUNK_ENGINE System::Logger<System::LOG_ERROR> out_error;
#endif	//	_DEBUG

#endif	//	_H_PUNK_SYSTEM_LOGGER
