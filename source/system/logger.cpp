#include "logger.h"

int Tab::m_offset = 0;

namespace System
{
	std::unique_ptr<Streamer> Streamer::m_instance;

	Streamer& Streamer::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new Streamer);
		return *m_instance.get();
	}

	void Streamer::Destroy()
	{
		m_instance.reset(0);
	}

		Streamer::Streamer()
		{
			string cur_time = System::Clock::SysTimeAsUTC();
			// cook a nice name for the log file
			cur_time[3] = cur_time[7] = cur_time[10] = cur_time[19] = 0;		//	split string into several strings
			const wchar_t* buf = cur_time.Data();
			//	makefile name according to the current date
			string filename(L"log_" + string(&buf[20]) + L"_" + string(&buf[4]) + L"_" + string(&buf[8]));
			m_stream.open(filename.ToStdString().c_str(), std::ios_base::app);
		}

		Streamer& Streamer::operator << (const string& s)
		{
			std::wcout << s.Data();
			if (m_stream.is_open())
				m_stream << s.Data();
			return *this;
		}

		Streamer& Streamer::operator << (const char* v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (const wchar_t* v)
		{
			std::wcout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (const std::string& v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v.c_str();
			return *this;
		}

		Streamer& Streamer::operator << (char v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (wchar_t v)
		{
			std::wcout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (unsigned char v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (short v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (unsigned short v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (long v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (unsigned long v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (int v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (unsigned int v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (__int64 v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (unsigned __int64 v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (float v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (double v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (long double v)
		{
			std::cout << v;
			if (m_stream.is_open())
				m_stream << v;
			return *this;
		}

		Streamer& Streamer::operator << (_Myt& (__cdecl *_Pfn)(_Myt&))
		{
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}

		Streamer& Streamer::operator << (_Myios& (__cdecl *_Pfn)(_Myios&))
		{
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}

		Streamer& Streamer::operator << (std::ios_base& (__cdecl *_Pfn)(std::ios_base&))
		{
			std::wcout << _Pfn;
			if (m_stream.is_open())
				m_stream << _Pfn;
			return *this;
		}
}

PUNK_ENGINE_PUBLIC System::Logger<System::LoggerType::Message> out_message;
PUNK_ENGINE_PUBLIC System::Logger<System::LoggerType::Warning> out_warning;
PUNK_ENGINE_PUBLIC System::Logger<System::LoggerType::Error> out_error;
