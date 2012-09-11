#include <sstream>
#include "profiler_win32.h"

namespace System
{
	//
	//	Implementation of profiler goes here
	//
	Profiler::Profiler()
	{
		QueryPerformanceFrequency(&m_frequency);
	}

	void Profiler::Start(const string& description)
	{
		m_description = description;
		QueryPerformanceCounter(&m_start);
	}

	__int64 Profiler::End()
	{
		QueryPerformanceCounter(&m_end);
		return m_end.QuadPart - m_start.QuadPart;
	}

	double Profiler::ToMiliseconds() const
	{
		return (m_end.QuadPart - m_start.QuadPart) * 1000 / (double)m_frequency.QuadPart;
	}

	const string Profiler::ToString() const
	{
		std::wstringstream stream;
		stream << m_description.Data() << L": " << (double(m_end.QuadPart - m_start.QuadPart)/double(m_frequency.QuadPart)*1000.0) << L" ms; " << m_end.QuadPart - m_start.QuadPart << L" ticks";
		return string(stream.str().c_str());
	}
}