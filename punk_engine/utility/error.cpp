#include "error.h"
#include "../system/system.h"

namespace Utility
{
	UtilityError::UtilityError() : std::exception(), m_w_what(0)
	{
	}

	UtilityError::UtilityError(const System::string& message) : std::exception()
	{
		System::Stack stack;
		m_w_what = message + stack.GetStackTrace();
	}

	UtilityError::~UtilityError()
	{
	}

	const System::string& UtilityError::w_what() const
	{
		return m_w_what;
	}
}