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
		m_timer.Reset();
	}

	long long Profiler::End()
	{
		return m_timer.GetElapsedTicks();
	}

	double Profiler::ToMiliseconds() const
	{
		return m_timer.GetElapsedMiliseconds();
	}

	const string Profiler::ToString() const
	{
		std::wstringstream stream;
		stream << m_description.Data() << L": " << m_timer.GetElapsedSeconds() << L" ms; " << m_timer.GetElapsedTicks() << L" ticks";
		return string(stream.str().c_str());
	}
}