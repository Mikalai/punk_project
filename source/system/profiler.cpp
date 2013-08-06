#include <sstream>
#include "profiler.h"

namespace System
{
	//
	//	Implementation of profiler goes here
	//
	Profiler::Profiler()
	{
	}

	void Profiler::Start(const string& description)
	{
		m_description = description;
        m_start_time = m_timer.GetCurrentTime();
        m_timer.Reset();
	}

    double Profiler::End()
	{
        return m_end_time = m_timer.GetCurrentTime();
	}

	double Profiler::ToMiliseconds() const
	{
        return (m_end_time - m_start_time) * 1000.0f;
	}

	const string Profiler::ToString() const
	{
		std::wstringstream stream;
        stream << m_description.Data() << L": " << ToMiliseconds() << L" ms; ";
		return string(stream.str().c_str());
	}
}
