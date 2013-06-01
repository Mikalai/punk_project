#include "exceptions.h"
#include "stack_trace.h"

namespace System
{
	PunkException::PunkException()
		: m_data(L"Punk exception")
	{
		m_data = GetStack() + m_data;
	}

	PunkException::PunkException(const System::string& data)
		: m_data(data)
	{
		m_data = GetStack() + m_data;
	}

	PunkException::~PunkException()
	{}
	
	const System::string PunkException::GetStack()
	{
		Stack stack;
		return stack.GetStackTrace();
	}

	const System::string& PunkException::ToString() const
	{
		return m_data;
	}
}