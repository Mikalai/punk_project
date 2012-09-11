#ifndef _H_PUNK_ERROR_WIN32
#define _H_PUNK_ERROR_WIN32

#include <exception>
#include "../../config.h"
#include "../../string/string.h"
#include "../error.h"

namespace System
{
	class PUNK_ENGINE SystemError : public std::exception
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

	class PUNK_ENGINE NotImplemented : public SystemError {};
	class PUNK_ENGINE FileNotFound : public SystemError {};
}

#endif