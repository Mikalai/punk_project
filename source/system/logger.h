#ifndef _H_PUNK_SYSTEM_LOGGER
#define _H_PUNK_SYSTEM_LOGGER

#include <memory>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "../config.h"
//#include "stack_trace.h"
#include "console.h"
#include "system_clock.h"
#include "../string/string.h"

namespace System
{
	enum LoggerType
	{
		LOG_NO = 0,
		LOG_MESSAGE = 0,
		LOG_WARNING = 1,
		LOG_ERROR = 2,
	};

	struct PUNK_ENGINE Streamer
	{
	private:
		typedef std::basic_ostream<wchar_t, std::char_traits<wchar_t>> _Myt;
		typedef std::basic_ios<wchar_t, std::char_traits<wchar_t>> _Myios;
	public:
		Streamer()
		{
			string cur_time = SystemClock::Instance()->NowAsUTC();
			// cook a nice name for the log file
			cur_time[3] = cur_time[7] = cur_time[10] = cur_time[19] = 0;		//	split string into several strings
			const wchar_t* buf = cur_time.Data();
			//	makefile name according to the current date
			string filename(L"log_" + string(&buf[20]) + L"_" + string(&buf[4]) + L"_" + string(&buf[8]));
			m_stream.open(filename.Data(), std::ios_base::app);
		}

		Streamer& operator << (const string& s)
		{
			std::wcout << s.Data();
			if (m_stream.is_open())
				m_stream << s.Data();
			return *this;
		}

		Streamer& operator << (const char* v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (const wchar_t* v)
		{
			std::wcout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (const std::string& v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v.c_str();
			return *this;
		}

		Streamer& operator << (char v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (wchar_t v)
		{
			std::wcout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (unsigned char v)
		{				
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (short v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (unsigned short v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (long v)
		{			
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (unsigned long v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (int v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (unsigned int v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (__int64 v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (unsigned __int64 v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (float v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (double v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (long double v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& operator << (_Myt& (__cdecl *_Pfn)(_Myt&))
		{
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}

		Streamer& operator << (_Myios& (__cdecl *_Pfn)(_Myios&))
		{	
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}	

		Streamer& operator << (std::ios_base& (__cdecl *_Pfn)(std::ios_base&))
		{	
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}		

		static Streamer& Instance();
		static void Destroy();

	private:
		static std::auto_ptr<Streamer> m_instance;

		std::ofstream m_stream;
	};

	//	wired message outputer, suitable only for ASCII symbols
	template<LoggerType type>
	class Logger
	{		
	public:

		Logger() {}

	public:

		Streamer& operator () ()
		{			
			Header<type>();
			return m_stream;
		}

	private:

		Streamer m_stream;

		template<LoggerType LT>
		void Header()
		{			
			Console::Instance()->SetTextColor(Console::COLOR_WHITE);
			Streamer::Instance() << SystemClock::Instance()->NowAsLocal();
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}

		template<>
		void Header<LOG_MESSAGE>()
		{
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGREEN);
			Streamer::Instance() << SystemClock::Instance()->NowAsLocal() << L": Message: ";
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}

		template<> 
		void Header<LOG_WARNING>()
		{
			Console::Instance()->SetTextColor(Console::COLOR_YELLOW);
			Streamer::Instance() << SystemClock::Instance()->NowAsLocal() << L": Warning: ";
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}

		//	special header for error
		template<>
		void Header<LOG_ERROR>()
		{
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTRED);
			Streamer::Instance()<< SystemClock::Instance()->NowAsLocal() << ": Error: ";			
			Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		}
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
extern PUNK_ENGINE System::Logger<System::LOG_MESSAGE> out_message;
extern PUNK_ENGINE System::Logger<System::LOG_WARNING> out_warning;
extern PUNK_ENGINE System::Logger<System::LOG_ERROR> out_error;
#else
extern PUNK_ENGINE System::Logger<System::LOG_MESSAGE> out_message;
extern PUNK_ENGINE System::Logger<System::LOG_WARNING> out_warning;
extern PUNK_ENGINE System::Logger<System::LOG_ERROR> out_error;
#endif	//	_DEBUG

#endif	//	_H_PUNK_SYSTEM_LOGGER