#ifndef _H_PUNK_ERROR_WIN32
#define _H_PUNK_ERROR_WIN32

#include <exception>
#include "../config.h"
#include "../string.h"
#include "../error.h"

namespace System
{
	class MODULE_SYSTEM SystemError : public std::exception
    {
    protected:
        string message;
    public:
        SystemError();
        virtual ~SystemError();
        SystemError(wchar_t* msg);
		SystemError(const string& msg);
		virtual const string& Message() const throw();
        virtual const char* what() const throw();
	private:
		string CheckOSError();
    };

	class MODULE_SYSTEM NotImplemented : public SystemError {};
	class MODULE_SYSTEM FileNotFound : public SystemError {};
}

#endif