#ifndef _H_PUNK_UTILITY_ERROR
#define _H_PUNK_UTILITY_ERROR

#include <exception>
#include "../system/string.h"
#include "config.h"

namespace Utility
{
	class LIB_UTILITY UtilityError : public std::exception
	{
	public:
		UtilityError();
		UtilityError(const System::string& message);
		~UtilityError();

		virtual const System::string& w_what() const;
	private:
		System::string m_w_what;
	};
}

#endif